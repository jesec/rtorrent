// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#include <algorithm>
#include <locale>
#include <torrent/exceptions.h>

#include "rpc/parse_options.h"

namespace rpc {

int
parse_option_flag(const std::string& option, parse_option_flag_type ftor) {
  auto first = option.begin();
  auto last  = option.end();

  first = std::find_if(first, last, [](char c) {
    return !std::isspace(c, std::locale::classic());
  });

  if (first == last)
    throw torrent::input_error(option);

  auto next = std::find_if(first, last, [](char c) {
    return !std::isalnum(c, std::locale::classic()) && c != '_';
  });

  if (first == next)
    throw torrent::input_error(option);

  if (std::find_if(next, last, [](char c) {
        return !std::isspace(c, std::locale::classic());
      }) != last)
    throw torrent::input_error(option);

  return ftor(std::string(first, next));
}

int
parse_option_flags(const std::string&     option,
                   parse_option_flag_type ftor,
                   int                    flags) {
  auto first = option.begin();
  auto last  = option.end();

  while (first != last) {
    first = std::find_if(first, last, [](char c) {
      return !std::isspace(c, std::locale::classic());
    });

    if (first == last)
      break;

    auto next = std::find_if(first, last, [](char c) {
      return !std::isalnum(c, std::locale::classic()) && c != '_';
    });

    if (first == next)
      throw torrent::input_error(option);

    int f = ftor(std::string(first, next));

    if (f < 0)
      flags &= f;
    else
      flags |= f;

    first = std::find_if(next, last, [](char c) {
      return !std::isspace(c, std::locale::classic());
    });

    if (first == last)
      break;

    if (*first++ != '|' || first == last)
      throw torrent::input_error(option);
  }

  return flags;
}

void
parse_option_for_each(const std::string& option, parse_option_flag_type ftor) {
  auto first = option.begin();
  auto last  = option.end();

  while (first != last) {
    first = std::find_if(first, last, [](char c) {
      return !std::isspace(c, std::locale::classic());
    });

    if (first == last)
      break;

    auto next = std::find_if(first, last, [](char c) {
      return !std::isalnum(c, std::locale::classic()) && c != '_';
    });

    if (first == next)
      throw torrent::input_error(option);

    ftor(std::string(first, next));

    first = std::find_if(next, last, [](char c) {
      return !std::isspace(c, std::locale::classic());
    });

    if (first == last)
      break;

    if (*first++ != '|' || first == last)
      throw torrent::input_error(option);
  }
}

std::string
parse_option_print_vector(
  int                                             flags,
  const std::vector<std::pair<const char*, int>>& flag_list) {
  std::string result;

  for (auto f : flag_list) {
    if (f.second < 0) {
      if ((flags & f.second) != flags)
        continue;
    } else {
      if ((flags & f.second) != f.second)
        continue;
    }

    if (!result.empty())
      result += '|';

    result += f.first;
  }

  return result;
}

std::string
parse_option_print_flags(unsigned int flags, parse_option_rflag_type ftor) {
  std::string result;

  for (int i = 1; flags != 0; i <<= 1) {
    if (!(flags & i))
      continue;

    if (!result.empty())
      result += '|';

    result += ftor(i);
    flags &= ~i;
  }

  return result;
}

}
