// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_RPC_SCGI_H
#define RTORRENT_RPC_SCGI_H

#include <string>

#include <torrent/buildinfo.h>
#include <torrent/event.h>

#include "utils/functional_fun.h"

#include "rpc/scgi_task.h"

namespace utils {
class SocketFd;
}

namespace rpc {

class lt_cacheline_aligned SCgi : public torrent::Event {
public:
  typedef utils::function2<bool, const char*, uint32_t> slot_write;

  static const int max_tasks = 100;

  // Global lock:
  SCgi()
    : m_logFd(-1) {}
  virtual ~SCgi();

  const char* type_name() const {
    return "scgi";
  }

  void open_port(void* sa, unsigned int length, bool dontRoute);
  void open_named(const std::string& filename);

  void activate();
  void deactivate();

  const std::string& path() const {
    return m_path;
  }

  int log_fd() const {
    return m_logFd;
  }
  void set_log_fd(int fd) {
    m_logFd = fd;
  }

  // Thread local:
  virtual void event_read();
  virtual void event_write();
  virtual void event_error();

  bool receive_call(SCgiTask* task, const char* buffer, uint32_t length);

  utils::SocketFd& get_fd() {
    return *reinterpret_cast<utils::SocketFd*>(&m_fileDesc);
  }

private:
  void open(void* sa, unsigned int length);

  std::string m_path;
  int         m_logFd;
  SCgiTask    m_task[max_tasks];
};

}

#endif
