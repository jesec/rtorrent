// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#include <memory>
#include <sstream>

#include <torrent/http.h>

#include "core/curl_get.h"
#include "core/http_queue.h"

namespace core {

HttpQueue::iterator
HttpQueue::insert(const std::string& url, std::iostream* s) {
  std::unique_ptr<CurlGet> h(m_slot_factory());

  h->set_url(url);
  h->set_stream(s);
  h->set_timeout(5 * 60);

  iterator signal_itr = base_type::insert(end(), h.get());

  h->signal_done().push_back([this, signal_itr] { erase(signal_itr); });
  h->signal_failed().push_back(
    [this, signal_itr](const auto&) { erase(signal_itr); });

  (*signal_itr)->start();

  h.release();

  for (signal_curl_get::iterator itr  = m_signal_insert.begin(),
                                 last = m_signal_insert.end();
       itr != last;
       itr++)
    (*itr)(*signal_itr);

  return signal_itr;
}

void
HttpQueue::erase(iterator signal_itr) {
  for (signal_curl_get::iterator itr  = m_signal_erase.begin(),
                                 last = m_signal_erase.end();
       itr != last;
       itr++)
    (*itr)(*signal_itr);

  delete *signal_itr;
  base_type::erase(signal_itr);
}

void
HttpQueue::clear() {
  while (!empty())
    erase(begin());

  base_type::clear();
}

}
