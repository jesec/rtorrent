// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2008, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_CORE_CURL_SOCKET_H
#define RTORRENT_CORE_CURL_SOCKET_H

#include <torrent/event.h>

#include "globals.h"

namespace core {

class CurlStack;

class CurlSocket : public torrent::Event {
public:
  CurlSocket(int fd, CurlStack* stack)
    : m_stack(stack) {
    m_fileDesc = fd;
  }
  ~CurlSocket();

  const char* type_name() const {
    return "curl";
  }

  void close();

  static int receive_socket(void*         easy_handle,
                            curl_socket_t fd,
                            int           what,
                            void*         userp,
                            void*         socketp);

private:
  CurlSocket(const CurlSocket&);
  void operator=(const CurlSocket&);

  virtual void event_read();
  virtual void event_write();
  virtual void event_error();

  CurlStack* m_stack;
};

}

#endif
