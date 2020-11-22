// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#include "config.h"

#include <torrent/exceptions.h>
#include <torrent/utils/file_stat.h>
#include <torrent/utils/path.h>

#include "file_status_cache.h"

namespace utils {

bool
FileStatusCache::insert(const std::string& path, int flags) {
  torrent::utils::file_stat fs;

  // Should we expand somewhere else? Problem is it adds a lot of junk
  // to the start of the paths added to the cache, causing more work
  // during search, etc.
  if (!fs.update(torrent::utils::path_expand(path)))
    return false;

  std::pair<iterator, bool> result =
    base_type::insert(value_type(path, file_status()));

  // Return false if the file hasn't been modified since last time. We
  // use 'equal to' instead of 'greater than' since the file might
  // have been replaced by another file, and thus should be re-tried.
  if (!result.second &&
      result.first->second.m_mtime == (uint32_t)fs.modified_time())
    return false;

  result.first->second.m_flags = 0;
  result.first->second.m_mtime = fs.modified_time();

  return true;
}

void
FileStatusCache::prune() {
  iterator itr = begin();

  while (itr != end()) {
    torrent::utils::file_stat fs;
    iterator                  tmp = itr++;

    if (!fs.update(torrent::utils::path_expand(tmp->first)) ||
        tmp->second.m_mtime != (uint32_t)fs.modified_time())
      base_type::erase(tmp);
  }
}

}
