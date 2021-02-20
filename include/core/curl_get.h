// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_CORE_CURL_GET_H
#define RTORRENT_CORE_CURL_GET_H

#include <iosfwd>
#include <string>

#include <curl/curl.h>
#include <torrent/http.h>
#include <torrent/utils/priority_queue_default.h>

namespace core {

class CurlStack;

class CurlGet final : public torrent::Http {
public:
  friend class CurlStack;

  CurlGet(CurlStack* s)
    : m_active(false)
    , m_handle(nullptr)
    , m_stack(s) {}
  ~CurlGet() override;
  CurlGet(const CurlGet&) = delete;
  void operator=(const CurlGet&) = delete;

  void start() override;
  void close() override;

  bool is_using_ipv6() {
    return m_ipv6;
  }
  void retry_ipv6();

  bool is_busy() const {
    return m_handle;
  }
  bool is_active() const {
    return m_active;
  }

  void set_active(bool a) {
    m_active = a;
  }

  double size_done();
  double size_total();

  CURL* handle() {
    return m_handle;
  }

private:
  void receive_timeout();

  bool m_active;
  bool m_ipv6;

  torrent::utils::priority_item m_taskTimeout;

  CURL*      m_handle;
  CurlStack* m_stack;
};

}

#endif
