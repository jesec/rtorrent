// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_RPC_PARSE_OPTIONS_H
#define RTORRENT_RPC_PARSE_OPTIONS_H

#include <cstring>
#include <functional>
#include <string>
#include <vector>

namespace rpc {

// If a flag returned by the functor is negative it is treated as a
// negation of the flag.

using parse_option_flag_type  = std::function<int(const std::string&)>;
using parse_option_rflag_type = std::function<const char*(unsigned int)>;

int
parse_option_flag(const std::string& option, parse_option_flag_type ftor);
int
parse_option_flags(const std::string&     option,
                   parse_option_flag_type ftor,
                   int                    flags = int());

void
parse_option_for_each(const std::string& option, parse_option_flag_type ftor);

std::string
parse_option_print_vector(
  int                                             flags,
  const std::vector<std::pair<const char*, int>>& flag_list);
std::string
parse_option_print_flags(unsigned int flags, parse_option_rflag_type ftor);

}

#endif
