// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_INPUT_BINDINGS_H
#define RTORRENT_INPUT_BINDINGS_H

#include <functional>
#include <map>

#include "display/attributes.h"

namespace input {

class Bindings : private std::map<int, std::function<void()>> {
public:
  typedef std::function<void()>    slot_void;
  typedef std::map<int, slot_void> base_type;

  using base_type::const_iterator;
  using base_type::const_reverse_iterator;
  using base_type::iterator;
  using base_type::reverse_iterator;

  using base_type::begin;
  using base_type::end;
  using base_type::find;
  using base_type::rbegin;
  using base_type::rend;

  using base_type::erase;

  using base_type::operator[];

  Bindings()
    : m_enabled(true) {}

  void enable() {
    m_enabled = true;
  }
  void disable() {
    m_enabled = false;
  }

  bool pressed(int key);

  void ignore(int key) {
    (*this)[key] = slot_void();
  }

private:
  bool m_enabled;
};

}

#endif
