// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#include "config.h"

#include <algorithm>
#include <dirent.h>
#include <functional>
#include <sys/stat.h>

#include <torrent/exceptions.h>
#include <torrent/utils/path.h>

#include "utils/directory.h"

namespace utils {

// Keep this?
bool
Directory::is_valid() const {
  if (m_path.empty())
    return false;

  DIR* d = opendir(torrent::utils::path_expand(m_path).c_str());
  closedir(d);

  return d;
}

bool
Directory::update(int flags) {
  if (m_path.empty())
    throw torrent::input_error(
      "Directory::update() tried to open an empty path.");

  DIR* d = opendir(torrent::utils::path_expand(m_path).c_str());

  if (d == NULL)
    return false;

  struct dirent* entry;
#ifdef __sun__
  struct stat s;
#endif

  while ((entry = readdir(d)) != NULL) {
    if ((flags & update_hide_dot) && entry->d_name[0] == '.')
      continue;

    iterator itr = base_type::insert(end(), value_type());

#ifdef __sun__
    stat(entry->d_name, &s);
    itr->d_fileno = entry->d_ino;
    itr->d_reclen = 0;
    itr->d_type   = s.st_mode;
#else
    itr->d_fileno = entry->d_fileno;
    itr->d_reclen = entry->d_reclen;
    itr->d_type   = entry->d_type;
#endif

#ifdef DIRENT_NAMLEN_EXISTS_FOOBAR
    itr->d_name = std::string(entry->d_name, entry->d_name + entry->d_namlen);
#else
    itr->d_name   = std::string(entry->d_name);
#endif
  }

  closedir(d);

  if (flags & update_sort)
    std::sort(begin(), end());

  return true;
}

}
