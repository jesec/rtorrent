// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_UTILS_SOCKET_FD_H
#define RTORRENT_UTILS_SOCKET_FD_H

#include <unistd.h>

#include <torrent/utils/socket_address.h>

namespace utils {

class SocketFd {
public:
  using priority_type = uint8_t;

  SocketFd() = default;
  explicit SocketFd(int fd)
    : m_fd(fd) {}

  bool is_valid() const {
    return m_fd >= 0;
  }

  int get_fd() const {
    return m_fd;
  }
  void set_fd(int fd) {
    m_fd = fd;
  }

  bool set_nonblock();
  bool set_reuse_address(bool state);
  bool set_dont_route(bool state);

  bool set_bind_to_device(const char* device);

  bool set_priority(priority_type p);

  bool set_send_buffer_size(uint32_t s);
  bool set_receive_buffer_size(uint32_t s);

  int get_error() const;

  bool open_stream();
  bool open_datagram();
  bool open_local();
  void close();

  void clear() {
    m_fd = -1;
  }

  bool bind(const torrent::utils::socket_address& sa);
  bool bind(const torrent::utils::socket_address& sa, unsigned int length);
  bool connect(const torrent::utils::socket_address& sa);
  bool getsockname(torrent::utils::socket_address* sa);

  bool     listen(int size);
  SocketFd accept(torrent::utils::socket_address* sa);

  //   unsigned int        get_read_queue_size() const;
  //   unsigned int        get_write_queue_size() const;

private:
  inline void check_valid() const;

  int  m_fd{ -1 };
  bool m_ipv6_socket{ false };
};

}

#endif
