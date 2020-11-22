// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#include "config.h"

#include <curl/curl.h>
#include <curl/easy.h>
#include <iostream>
#include <torrent/exceptions.h>

#include "core/curl_get.h"
#include "core/curl_stack.h"
#include "globals.h"

namespace core {

size_t
curl_get_receive_write(void* data, size_t size, size_t nmemb, void* handle) {
  if (!((CurlGet*)handle)
         ->stream()
         ->write((const char*)data, size * nmemb)
         .fail())
    return size * nmemb;
  else
    return 0;
}

CurlGet::~CurlGet() noexcept(true) {
  close();
}

void
CurlGet::start() {
  if (is_busy())
    throw torrent::internal_error(
      "Tried to call CurlGet::start on a busy object.");

  if (m_stream == NULL)
    throw torrent::internal_error(
      "Tried to call CurlGet::start without a valid output stream.");

  m_handle = curl_easy_init();

  if (m_handle == NULL)
    throw torrent::internal_error("Call to curl_easy_init() failed.");

  curl_easy_setopt(m_handle, CURLOPT_URL, m_url.c_str());
  curl_easy_setopt(m_handle, CURLOPT_WRITEFUNCTION, &curl_get_receive_write);
  curl_easy_setopt(m_handle, CURLOPT_WRITEDATA, this);

  if (m_timeout != 0) {
    curl_easy_setopt(m_handle, CURLOPT_CONNECTTIMEOUT, (long)60);
    curl_easy_setopt(m_handle, CURLOPT_TIMEOUT, (long)m_timeout);

    // Normally libcurl should handle the timeout. But sometimes that doesn't
    // work right so we do a fallback timeout that just aborts the transfer.
    m_taskTimeout.slot() = std::bind(&CurlGet::receive_timeout, this);
    priority_queue_erase(&taskScheduler, &m_taskTimeout);
    priority_queue_insert(&taskScheduler,
                          &m_taskTimeout,
                          cachedTime +
                            torrent::utils::timer::from_seconds(m_timeout + 5));
  }

  curl_easy_setopt(m_handle, CURLOPT_FORBID_REUSE, (long)1);
  curl_easy_setopt(m_handle, CURLOPT_NOSIGNAL, (long)1);
  curl_easy_setopt(m_handle, CURLOPT_FOLLOWLOCATION, (long)1);
  curl_easy_setopt(m_handle, CURLOPT_MAXREDIRS, (long)5);

  curl_easy_setopt(m_handle, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_WHATEVER);

  curl_easy_setopt(m_handle, CURLOPT_ENCODING, "");

  m_ipv6 = false;

  m_stack->add_get(this);
}

void
CurlGet::close() {
  priority_queue_erase(&taskScheduler, &m_taskTimeout);
  if (!is_busy())
    return;

  m_stack->remove_get(this);

  curl_easy_cleanup(m_handle);

  m_handle = NULL;
}

void
CurlGet::retry_ipv6() {
  CURL* nhandle = curl_easy_duphandle(m_handle);

  curl_easy_setopt(nhandle, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V6);
  curl_easy_cleanup(m_handle);

  m_handle = nhandle;
  m_ipv6   = true;
}

void
CurlGet::receive_timeout() {
  return m_stack->transfer_done(m_handle, "Timed out");
}

double
CurlGet::size_done() {
  double d = 0.0;
  curl_easy_getinfo(m_handle, CURLINFO_SIZE_DOWNLOAD, &d);

  return d;
}

double
CurlGet::size_total() {
  double d = 0.0;
  curl_easy_getinfo(m_handle, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &d);

  return d;
}

}
