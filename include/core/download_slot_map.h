// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_CORE_DOWNLOAD_SLOT_MAP_H
#define RTORRENT_CORE_DOWNLOAD_SLOT_MAP_H

#include <functional>
#include <map>
#include <string>

#include "core/download.h"

namespace core {

class DownloadSlotMap
  : public std::map<std::string, std::function<void(Download*)>> {
public:
  typedef std::function<void(Download*)>       slot_download;
  typedef std::map<std::string, slot_download> Base;

  void insert(const std::string& key, slot_download s) {
    Base::operator[](key) = s;
  }
  void erase(const std::string& key) {
    Base::erase(key);
  }

  void for_each(Download* d);
};

inline void
DownloadSlotMap::for_each(Download* d) {
  for (iterator itr = begin(), last = end(); itr != last; ++itr)
    itr->second(d);
}

}

#endif
