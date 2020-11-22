// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#include <algorithm>
#include <cctype>
#include <cerrno>
#include <cstdio>
#include <cstring>
#include <fcntl.h>
#include <signal.h>
#include <sstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "utils/lockfile.h"

namespace utils {

struct lockfile_valid_char {
  bool operator()(char c) {
    return !std::isgraph(c);
  }
};

struct lockfile_valid_hostname {
  bool operator()(char c) {
    return !std::isgraph(c) || c == ':';
  }
};

bool
Lockfile::is_stale() {
  process_type process = locked_by();

  char buf[256];

  if (process.second <= 0 || ::gethostname(buf, 255) != 0 ||
      buf != process.first)
    return false;

  return ::kill(process.second, 0) != 0 && errno != EPERM;
}

bool
Lockfile::try_lock() {
  if (m_path.empty()) {
    m_locked = true;
    return true;
  }

  if (is_stale())
    ::unlink(m_path.c_str());

  // Just do a simple locking for now that isn't safe for network
  // devices.
  int fd = ::open(m_path.c_str(), O_RDWR | O_CREAT | O_EXCL, 0444);

  if (fd == -1)
    return false;

  char buf[256];
  int  pos = ::gethostname(buf, 255);

  if (pos == 0) {
    ::snprintf(buf + std::strlen(buf), 255, ":+%i\n", ::getpid());
    ::write(fd, buf, std::strlen(buf));
  }

  ::close(fd);

  m_locked = true;
  return true;
}

bool
Lockfile::unlock() {
  m_locked = false;

  if (m_path.empty())
    return true;
  else
    return ::unlink(m_path.c_str()) != -1;
}

Lockfile::process_type
Lockfile::locked_by() const {
  int fd = ::open(m_path.c_str(), O_RDONLY);

  if (fd < 0)
    return process_type(std::string(), 0);

  char  first[256];
  char* last = first + std::max<ssize_t>(read(fd, first, 255), 0);

  *last = '\0';
  ::close(fd);

  char* endHostname = std::find_if(first, last, lockfile_valid_hostname());
  char* beginPid    = endHostname;
  char* endPid;

  long long int pid;

  if (beginPid + 2 >= last || *(beginPid++) != ':' || *(beginPid++) != '+' ||
      (pid = strtoll(beginPid, &endPid, 10)) == 0 || endPid == NULL)
    return process_type(std::string(), 0);

  return process_type(std::string(first, endHostname), pid);
}

std::string
Lockfile::locked_by_as_string() const {
  process_type p = locked_by();

  if (p.first.empty())
    return "<error>";

  std::stringstream str;
  str << p.first << ":+" << p.second;

  return str.str();
}

}
