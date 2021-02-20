// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_INPUT_TEXT_INPUT_H
#define RTORRENT_INPUT_TEXT_INPUT_H

#include <string>

#include "input/bindings.h"

namespace input {

class TextInput : private std::string {
public:
  using Base      = std::string;
  using slot_void = std::function<void()>;

  using Base::c_str;
  using Base::empty;
  using Base::npos;
  using Base::size;
  using Base::size_type;

  virtual ~TextInput() = default;

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
  size_type m_pos{ 0 };

  slot_void m_slot_dirty;

  Bindings m_bindings;
};

}

#endif
