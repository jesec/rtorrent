// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_RPC_SCGI_TASK_H
#define RTORRENT_RPC_SCGI_TASK_H

#include <torrent/event.h>

namespace utils {
class SocketFd;
}

namespace rpc {

class SCgi;

class SCgiTask : public torrent::Event {
public:
  static constexpr unsigned int default_buffer_size = 2047;
  static constexpr int          max_header_size     = 2000;
  static constexpr int          max_content_size    = (2 << 23);

  SCgiTask() {
    m_fileDesc = -1;
  }

  bool is_open() const {
    return m_fileDesc != -1;
  }
  bool is_available() const {
    return m_fileDesc == -1;
  }

  void open(SCgi* parent, int fd);
  void close();

  virtual void event_read();
  virtual void event_write();
  virtual void event_error();

  bool receive_write(const char* buffer, uint32_t length);

  utils::SocketFd& get_fd() {
    return *reinterpret_cast<utils::SocketFd*>(&m_fileDesc);
  }

private:
  inline void realloc_buffer(uint32_t    size,
                             const char* buffer,
                             uint32_t    bufferSize);

  SCgi* m_parent;

  char* m_buffer;
  char* m_position;
  char* m_body;

  unsigned int m_bufferSize;
};

}

#endif
