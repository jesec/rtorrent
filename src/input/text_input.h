// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_INPUT_TEXT_INPUT_H
#define RTORRENT_INPUT_TEXT_INPUT_H

#include <string>

#include "bindings.h"

namespace input {

class TextInput : private std::string {
public:
  typedef std::string           Base;
  typedef std::function<void()> slot_void;

  using Base::c_str;
  using Base::empty;
  using Base::npos;
  using Base::size;
  using Base::size_type;

  TextInput()
    : m_pos(0) {}
  virtual ~TextInput() {}

  size_type get_pos() {
    return m_pos;
  }
  void set_pos(size_type pos) {
    m_pos = pos;
  }

  virtual bool pressed(int key);

  void clear() {
    m_pos = 0;
    Base::clear();
  }

  void slot_dirty(slot_void s) {
    m_slot_dirty = s;
  }
  void mark_dirty() {
    if (m_slot_dirty)
      m_slot_dirty();
  }

  std::string& str() {
    return *this;
  }

  Bindings& bindings() {
    return m_bindings;
  }

private:
  size_type m_pos;

  slot_void m_slot_dirty;

  Bindings m_bindings;
};

}

#endif
