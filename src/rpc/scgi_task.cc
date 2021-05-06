// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#include <cstdio>
#include <string_view>
#include <sys/socket.h>
#include <sys/types.h>
#include <torrent/exceptions.h>
#include <torrent/poll.h>
#include <torrent/utils/allocators.h>
#include <torrent/utils/error_number.h>
#include <torrent/utils/log.h>

#include "control.h"
#include "globals.h"
#include "utils/socket_fd.h"

#include "rpc/scgi.h"

// Test:
// #include "core/manager.h"
// #include <torrent/utils/timer.h>

// static torrent::utils::timer scgiTimer;

namespace rpc {

inline void
SCgiTask::realloc_buffer(uint32_t    size,
                         const char* buffer,
                         uint32_t    bufferSize) {
  char* tmp = torrent::utils::cacheline_allocator<char>::alloc_size(size);

  if (buffer != nullptr && bufferSize > 0) {
    std::memcpy(tmp, buffer, bufferSize);
  }

  ::free(m_buffer);
  m_buffer = tmp;
}

void
SCgiTask::open(SCgi* parent, int fd) {
  m_parent   = parent;
  m_fileDesc = fd;
  m_buffer   = torrent::utils::cacheline_allocator<char>::alloc_size(
    (m_bufferSize = default_buffer_size) + 1);
  m_position = m_buffer;
  m_body     = nullptr;

  worker_thread->poll()->open(this);
  worker_thread->poll()->insert_read(this);
  worker_thread->poll()->insert_error(this);

  //   scgiTimer = torrent::utils::timer::current();
}

void
SCgiTask::close() {
  if (!get_fd().is_valid())
    return;

  worker_thread->poll()->remove_read(this);
  worker_thread->poll()->remove_write(this);
  worker_thread->poll()->remove_error(this);
  worker_thread->poll()->close(this);

  get_fd().close();
  get_fd().clear();

  ::free(m_buffer);
  m_buffer = nullptr;

  // Test
  //   char buffer[512];
  //   sprintf(buffer, "SCgi system call processed: %i",
  //   (int)(torrent::utils::timer::current() - scgiTimer).usec());
  //   control->core()->push_log(std::string(buffer));
}

void
SCgiTask::event_read() {
  int bytes =
    ::recv(m_fileDesc, m_position, m_bufferSize - (m_position - m_buffer), 0);

  if (bytes <= 0) {
    if (bytes == 0 ||
        !torrent::utils::error_number::current().is_blocked_momentary())
      close();

    return;
  }

  // The buffer has space to nul-terminate to ease the parsing below.
  m_position += bytes;
  *m_position = '\0';

  if (m_body == nullptr) {
    // Don't bother caching the parsed values, as we're likely to
    // receive all the data we need the first time.
    char* current;

    int contentSize;
    int headerSize = strtol(m_buffer, &current, 0);

    if (current == m_position)
      return;

    // If the request doesn't start with an integer or if it didn't
    // end in ':', then close the connection.
    if (current == m_buffer || *current != ':' || headerSize < 17 ||
        headerSize > max_header_size)
      goto event_read_failed;

    if (std::distance(++current, m_position) < headerSize + 1)
      return;

    const std::string_view header(current, headerSize);

    // RFC 3875, 4.1.2
    const auto contentLengthPos = header.find("CONTENT_LENGTH");
    if (contentLengthPos == std::string_view::npos) {
      goto event_read_failed;
    }

    char* contentPos;

    // length of "CONTENT_LENGTH" -> 14
    contentSize =
      strtol(header.data() + contentLengthPos + 14 + 1, &contentPos, 0);

    if (*contentPos != '\0' || contentSize <= 0)
      goto event_read_failed;

    // RFC 3875, 4.1.3
    const auto contentTypePos = header.find("CONTENT_TYPE");
    if (contentTypePos != std::string_view::npos) {
      // length of "CONTENT_TYPE" -> 12
      const auto contentTypeStartPos = contentTypePos + 12 + 1;
      const auto contentTypeEndPos   = header.find('\0', contentTypeStartPos);

      if (contentTypeEndPos == std::string_view::npos) {
        goto event_read_failed;
      }

      const auto contentTypeSize = contentTypeEndPos - contentTypeStartPos;
      const auto contentType =
        header.substr(contentTypeStartPos, contentTypeSize);

      if (contentType.find("application/json") != std::string_view::npos) {
        // RFC 4627, 6
        m_type = ContentType::JSON;
      } else if (contentType.find("text/xml") != std::string_view::npos) {
        // Winer, D., "XML-RPC Specification", Header requirements
        m_type = ContentType::XML;
      } else {
        goto event_read_failed;
      }
    } else {
      m_type = ContentType::XML;
    }

    m_body     = current + headerSize + 1;
    headerSize = std::distance(m_buffer, m_body);

    if ((unsigned int)(contentSize + headerSize) < m_bufferSize) {
      m_bufferSize = contentSize + headerSize;

    } else if ((unsigned int)contentSize <= default_buffer_size) {
      m_bufferSize = contentSize;

      std::memmove(m_buffer, m_body, std::distance(m_body, m_position));
      m_position = m_buffer + std::distance(m_body, m_position);
      m_body     = m_buffer;

    } else {
      realloc_buffer((m_bufferSize = contentSize) + 1,
                     m_body,
                     std::distance(m_body, m_position));

      m_position = m_buffer + std::distance(m_body, m_position);
      m_body     = m_buffer;
    }
  }

  if ((unsigned int)std::distance(m_buffer, m_position) != m_bufferSize)
    return;

  worker_thread->poll()->remove_read(this);
  worker_thread->poll()->insert_write(this);

  if (m_parent->log_fd() >= 0) {
    ssize_t __attribute__((unused)) result;
    // Clean up logging, this is just plain ugly...
    //    write(m_logFd, "\n---\n", sizeof("\n---\n"));
    result = write(m_parent->log_fd(), m_buffer, m_bufferSize);
    result = write(m_parent->log_fd(), "\n---\n", sizeof("\n---\n"));
  }

  lt_log_print_dump(torrent::LOG_RPC_DUMP,
                    m_body,
                    m_bufferSize - std::distance(m_buffer, m_body),
                    "scgi",
                    "RPC read.",
                    0);

  // Close if the call failed, else stay open to write back data.
  if (!m_parent->receive_call(
        this, m_body, m_bufferSize - std::distance(m_buffer, m_body)))
    close();

  return;

event_read_failed:
  //   throw torrent::internal_error("SCgiTask::event_read() fault not
  //   handled.");
  close();
}

void
SCgiTask::event_write() {
  int bytes = ::send(m_fileDesc, m_position, m_bufferSize, 0);

  if (bytes == -1) {
    if (!torrent::utils::error_number::current().is_blocked_momentary())
      close();

    return;
  }

  m_position += bytes;
  m_bufferSize -= bytes;

  if (bytes == 0 || m_bufferSize == 0)
    return close();
}

void
SCgiTask::event_error() {
  close();
}

bool
SCgiTask::receive_write(const char* buffer, uint32_t length) {
  if (buffer == nullptr || length > (100 << 20))
    throw torrent::internal_error(
      "SCgiTask::receive_write(...) received bad input.");

  if (length + 256 > std::max(m_bufferSize, default_buffer_size))
    realloc_buffer(length + 256);

  const auto header = m_type == ContentType::JSON
                        ? "Status: 200 OK\r\nContent-Type: "
                          "application/json\r\nContent-Length: %i\r\n\r\n"
                        : "Status: 200 OK\r\nContent-Type: "
                          "text/xml\r\nContent-Length: %i\r\n\r\n";

  // Who ever bothers to check the return value?
  int headerSize = sprintf(m_buffer, header, length);

  m_position   = m_buffer;
  m_bufferSize = length + headerSize;

  std::memcpy(m_buffer + headerSize, buffer, length);

  if (m_parent->log_fd() >= 0) {
    ssize_t __attribute__((unused)) result;
    // Clean up logging, this is just plain ugly...
    //    write(m_logFd, "\n---\n", sizeof("\n---\n"));
    result = write(m_parent->log_fd(), m_buffer, m_bufferSize);
    result = write(m_parent->log_fd(), "\n---\n", sizeof("\n---\n"));
  }

  lt_log_print_dump(
    torrent::LOG_RPC_DUMP, m_buffer, m_bufferSize, "scgi", "RPC write.", 0);

  event_write();
  return true;
}

}
