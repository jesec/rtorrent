// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_RPC_IP_TABLE_LISTS_H
#define RTORRENT_RPC_IP_TABLE_LISTS_H

#include <algorithm>
#include <functional>
#include <string>
#include <torrent/utils/extents.h>
#include <vector>

namespace rpc {

typedef torrent::extents<uint32_t, int> ipv4_table;

struct ip_table_node {
  std::string name;
  ipv4_table  table;

  bool equal_name(const std::string& str) const {
    return str == name;
  }
};

class ip_table_list : private std::vector<ip_table_node> {
public:
  typedef std::vector<ip_table_node> base_type;

  using base_type::const_iterator;
  using base_type::iterator;
  using base_type::value_type;

  using base_type::begin;
  using base_type::end;

  iterator insert(const std::string& name);
  iterator find(const std::string& name);
};

inline ip_table_list::iterator
ip_table_list::insert(const std::string& name) {
  ip_table_node tmp = { name };

  return base_type::insert(end(), tmp);
}

inline ip_table_list::iterator
ip_table_list::find(const std::string& name) {
  for (iterator itr = begin(), last = end(); itr != last; itr++)
    if (itr->equal_name(name))
      return itr;

  return end();
}

}

#endif
