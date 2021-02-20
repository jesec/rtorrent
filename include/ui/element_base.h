// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_UI_ELEMENT_BASE_H
#define RTORRENT_UI_ELEMENT_BASE_H

#include "input/bindings.h"

namespace display {
class Frame;
class Window;
}

namespace ui {

class ElementBase {
public:
  using slot_type = std::function<void()>;

  virtual ~ElementBase() = default;

  bool is_active() const {
    return m_frame != nullptr;
  }

  input::Bindings& bindings() {
    return m_bindings;
  }

  virtual void activate(display::Frame* frame, bool focus = true) = 0;
  virtual void disable()                                          = 0;

  void slot_exit(const slot_type& s) {
    m_slot_exit = s;
  }

  void mark_dirty();

protected:
  display::Frame* m_frame{ nullptr };
  bool            m_focus{ false };

  input::Bindings m_bindings;
  slot_type       m_slot_exit;
};

}

#endif
