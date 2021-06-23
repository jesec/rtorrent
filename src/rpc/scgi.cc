// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#include <sys/stat.h>
#include <sys/un.h>

#include <torrent/connection_manager.h>
#include <torrent/exceptions.h>
#include <torrent/poll.h>
#include <torrent/torrent.h>
#include <torrent/utils/error_number.h>
#include <torrent/utils/socket_address.h>

#include "control.h"
#include "globals.h"
#include "rpc/parse_commands.h"
#include "utils/socket_fd.h"

#include "rpc/scgi.h"

namespace rpc {

SCgi::~SCgi() {
  if (!get_fd().is_valid())
    return;

  for (SCgiTask *itr = m_task, *last = m_task + max_tasks; itr != last; ++itr)
    if (itr->is_open())
      itr->close();

  deactivate();

  if (torrent::is_initialized()) {
    torrent::connection_manager()->dec_socket_count();
  }

  get_fd().close();
  get_fd().clear();

  if (!m_path.empty())
    ::unlink(m_path.c_str());
}

void
SCgi::open_port(void* sa, unsigned int length, bool dontRoute) {
  if (!get_fd().open_stream() || (dontRoute && !get_fd().set_dont_route(true)))
    throw torrent::resource_error(
      "Could not open socket for listening: " +
      torrent::utils::error_number::current().message());

  open(sa, length);
}

void
SCgi::open_named(const std::string& filename) {
  if (filename.empty() || filename.size() > 4096)
    throw torrent::resource_error("Invalid filename length.");

  char* buffer = static_cast<char*>(
    calloc(sizeof(char), sizeof(sockaddr_un) + filename.size()));
  sockaddr_un* sa = reinterpret_cast<sockaddr_un*>(buffer);

#ifdef __sun__
  sa->sun_family = AF_UNIX;
#else
  sa->sun_family = AF_LOCAL;
#endif

  std::memcpy(sa->sun_path, filename.c_str(), filename.size() + 1);

  if (!get_fd().open_local())
    throw torrent::resource_error("Could not open socket for listening.");

  // 700 permission by default
  fchmod(get_fd().get_fd(), S_IRWXU);

  open(sa, offsetof(struct sockaddr_un, sun_path) + filename.size() + 1);

  free(buffer);

  m_path = filename;
}

void
SCgi::open(void* sa, unsigned int length) {
  try {
    if (!get_fd().set_nonblock() || !get_fd().set_reuse_address(true) ||
        !get_fd().bind(*reinterpret_cast<torrent::utils::socket_address*>(sa),
                       length) ||
        !get_fd().listen(max_tasks))
      throw torrent::resource_error(
        "Could not prepare socket for listening: " +
        torrent::utils::error_number::current().message());

    torrent::connection_manager()->inc_socket_count();

  } catch (torrent::resource_error& e) {
    get_fd().close();
    get_fd().clear();

    throw e;
  }
}

void
SCgi::activate() {
  worker_thread->poll()->open(this);
  worker_thread->poll()->insert_read(this);
  worker_thread->poll()->insert_error(this);
}

void
SCgi::deactivate() {
  worker_thread->poll()->remove_read(this);
  worker_thread->poll()->remove_error(this);
  worker_thread->poll()->close(this);
}

void
SCgi::event_read() {
  torrent::utils::socket_address sa;
  utils::SocketFd                fd;

  while ((fd = get_fd().accept(&sa)).is_valid()) {
    SCgiTask* task =
      std::find_if(m_task, m_task + max_tasks, [](SCgiTask& task) {
        return task.is_available();
      });

    if (task == m_task + max_tasks) {
      // Ergh... just closing for now.
      fd.close();
      continue;
    }

    task->open(this, fd.get_fd());
  }
}

void
SCgi::event_write() {
  throw torrent::internal_error("Listener does not support write().");
}

void
SCgi::event_error() {
  throw torrent::internal_error("SCGI listener port received an error event.");
}

bool
SCgi::receive_call(SCgiTask* task, const char* buffer, uint32_t length) {
  bool       result   = false;
  const auto callback = [task](const char* buffer, uint32_t length) {
    return task->receive_write(buffer, length);
  };

  switch (task->type()) {
    case SCgiTask::ContentType::JSON:
      result =
        rpc.dispatch(RpcManager::RPCType::JSON, buffer, length, callback);
      break;
    case SCgiTask::ContentType::XML:
    default:
      torrent::thread_base::acquire_global_lock();
      torrent::main_thread()->interrupt();
      result = rpc.dispatch(RpcManager::RPCType::XML, buffer, length, callback);
      torrent::thread_base::release_global_lock();
  }

  return result;
}

}
