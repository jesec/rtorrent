// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_DISPLAY_WINDOW_HTTP_QUEUE_H
#define RTORRENT_DISPLAY_WINDOW_HTTP_QUEUE_H

#include <functional>

#include "display/window.h"

namespace core {
class CurlGet;
class HttpQueue;
}

namespace display {

class WindowHttpQueue : public Window {
public:
  using slot_curl_get   = std::function<void(core::CurlGet*)>;
  using signal_curl_get = std::list<slot_curl_get>;

  WindowHttpQueue(core::HttpQueue* q);

  void redraw() override;

private:
  struct Node {
    Node(core::CurlGet* h, const std::string& n)
      : m_http(h)
      , m_name(n) {}

    core::CurlGet* get_http() {
      return m_http;
    }

    core::CurlGet*        m_http;
    std::string           m_name;
    torrent::utils::timer m_timer;
  };

  using Container = std::list<Node>;

  void cleanup_list();

  void receive_insert(core::CurlGet* h);
  void receive_erase(core::CurlGet* h);

  static std::string create_name(core::CurlGet* h);

  core::HttpQueue* m_queue;
  Container        m_container;

  signal_curl_get::iterator m_connInsert;
  signal_curl_get::iterator m_connErase;
};

}

#endif
