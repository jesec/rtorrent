// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_CORE_HTTP_QUEUE_H
#define RTORRENT_CORE_HTTP_QUEUE_H

#include <functional>
#include <iosfwd>
#include <list>

namespace core {

class CurlGet;

class HttpQueue : private std::list<CurlGet*> {
public:
  using base_type       = std::list<CurlGet*>;
  using slot_factory    = std::function<CurlGet*()>;
  using slot_curl_get   = std::function<void(CurlGet*)>;
  using signal_curl_get = std::list<slot_curl_get>;

  using base_type::const_iterator;
  using base_type::const_reverse_iterator;
  using base_type::iterator;
  using base_type::reverse_iterator;

  using base_type::begin;
  using base_type::end;
  using base_type::rbegin;
  using base_type::rend;

  using base_type::empty;
  using base_type::size;

  ~HttpQueue() {
    clear();
  }

  // Note that any slots connected to the CurlGet signals must be
  // pushed in front of the erase slot added by HttpQueue::insert.
  //
  // Consider adding a flag to indicate whetever HttpQueue should
  // delete the stream.
  iterator insert(const std::string& url, std::iostream* s);
  void     erase(iterator itr);

  void clear();

  void set_slot_factory(slot_factory s) {
    m_slot_factory = s;
  }

  signal_curl_get& signal_insert() {
    return m_signal_insert;
  }
  signal_curl_get& signal_erase() {
    return m_signal_erase;
  }

private:
  slot_factory    m_slot_factory;
  signal_curl_get m_signal_insert;
  signal_curl_get m_signal_erase;
};

}

#endif
