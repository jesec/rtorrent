// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#include "config.h"

#include <cstdio>
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

// If bufferSize is zero then memcpy won't do anything.
inline void
SCgiTask::realloc_buffer(uint32_t    size,
                         const char* buffer,
                         uint32_t    bufferSize) {
  char* tmp = torrent::utils::cacheline_allocator<char>::alloc_size(size);

  std::memcpy(tmp, buffer, bufferSize);
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
  m_body     = NULL;

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
  m_buffer = NULL;

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

  if (m_body == NULL) {
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

    if (std::memcmp(current, "CONTENT_LENGTH", 15) != 0)
      goto event_read_failed;

    char* contentPos;
    contentSize = strtol(current + 15, &contentPos, 0);

    if (*contentPos != '\0' || contentSize <= 0 ||
        contentSize > max_content_size)
      goto event_read_failed;

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
    // Clean up logging, this is just plain ugly...
    //    write(m_logFd, "\n---\n", sizeof("\n---\n"));
    write(m_parent->log_fd(), m_buffer, m_bufferSize);
    write(m_parent->log_fd(), "\n---\n", sizeof("\n---\n"));
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
  if (buffer == NULL || length > (100 << 20))
    throw torrent::internal_error(
      "SCgiTask::receive_write(...) received bad input.");

  // Need to cast due to a bug in MacOSX gcc-4.0.1.
  if (length + 256 > std::max(m_bufferSize, (unsigned int)default_buffer_size))
    realloc_buffer(length + 256, NULL, 0);

  // Who ever bothers to check the return value?
  int headerSize = sprintf(
    m_buffer,
    "Status: 200 OK\r\nContent-Type: text/xml\r\nContent-Length: %i\r\n\r\n",
    length);

  m_position   = m_buffer;
  m_bufferSize = length + headerSize;

  std::memcpy(m_buffer + headerSize, buffer, length);

  if (m_parent->log_fd() >= 0) {
    int result;
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
