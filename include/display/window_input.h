// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_DISPLAY_WINDOW_INPUT_H
#define RTORRENT_DISPLAY_WINDOW_INPUT_H

#include <string>

#include "display/window.h"

namespace input {
class TextInput;
}

namespace display {

class WindowInput : public Window {
public:
  WindowInput()
    : Window(new Canvas, 0, 0, 1, extent_full, 1) {}

  input::TextInput* input() {
    return m_input;
  }
  void set_input(input::TextInput* input) {
    m_input = input;
  }

  const std::string& title() const {
    return m_title;
  }
  void set_title(const std::string& str) {
    m_title = str;
  }

  bool focus() const {
    return m_focus;
  }
  void set_focus(bool f) {
    m_focus = f;
    if (is_active())
      mark_dirty();
  }

  void redraw() override;

private:
  input::TextInput* m_input{ nullptr };
  std::string       m_title;

  bool m_focus{ false };
};

}

#endif
