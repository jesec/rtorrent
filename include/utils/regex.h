// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2007, Jari Sundell <jaris@ifi.uio.no>

// This is a hacked up whole string pattern matching. Replace with
// TR1's regex when that becomes widely available. It is intended for
// small strings.

#ifndef RTORRENT_UTILS_REGEX_H
#define RTORRENT_UTILS_REGEX_H

#include <sys/types.h>

#include <algorithm>
#include <functional>
#include <list>
#include <string>

namespace utils {

class regex : public std::unary_function<std::string, bool> {
public:
  regex() {}
  regex(const std::string& p)
    : m_pattern(p) {}

  const std::string& pattern() const {
    return m_pattern;
  }

  bool operator()(const std::string& p) const;

private:
  std::string m_pattern;
};

// This isn't optimized, or very clean. A simple hack that should work.
inline bool
regex::operator()(const std::string& text) const {
  if (m_pattern.empty() || text.empty() ||
      (m_pattern[0] != '*' && m_pattern[0] != text[0]))
    return false;

  // Replace with unordered_vector?
  std::list<unsigned int> paths;
  paths.push_front(0);

  for (std::string::const_iterator itrText  = ++text.begin(),
                                   lastText = text.end();
       itrText != lastText;
       ++itrText) {

    for (std::list<unsigned int>::iterator itrPaths  = paths.begin(),
                                           lastPaths = paths.end();
         itrPaths != lastPaths;) {

      unsigned int next = *itrPaths + 1;

      if (m_pattern[*itrPaths] != '*')
        itrPaths = paths.erase(itrPaths);
      else
        itrPaths++;

      // When we reach the end of 'm_pattern', we don't have a whole
      // match of 'text'.
      if (next == m_pattern.size())
        continue;

      // Push to the back so that '*' will match zero length strings.
      if (m_pattern[next] == '*')
        paths.push_back(next);

      if (m_pattern[next] == *itrText)
        paths.push_front(next);
    }

    if (paths.empty())
      return false;
  }

  return std::find(paths.begin(), paths.end(), m_pattern.size() - 1) !=
         paths.end();
}

} // namespace utils

#endif
