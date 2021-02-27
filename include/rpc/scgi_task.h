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

  enum ContentType { XML, JSON };

  SCgiTask() {
    m_fileDesc = -1;
  }

  ContentType type() const {
    return m_type;
  }

  bool is_open() const {
    return m_fileDesc != -1;
  }
  bool is_available() const {
    return m_fileDesc == -1;
  }

  void open(SCgi* parent, int fd);
  void close();

  void event_read() override;
  void event_write() override;
  void event_error() override;

  bool receive_write(const char* buffer, uint32_t length);

  utils::SocketFd& get_fd() {
    return *reinterpret_cast<utils::SocketFd*>(&m_fileDesc);
  }

private:
  inline void realloc_buffer(uint32_t    size,
                             const char* buffer     = nullptr,
                             uint32_t    bufferSize = 0);

  ContentType m_type{ XML };

  SCgi* m_parent;

  char* m_buffer;
  char* m_position;
  char* m_body;

  unsigned int m_bufferSize;
};

}

#endif
