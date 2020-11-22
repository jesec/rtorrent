// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#include "display/attributes.h"

#include "input/text_input.h"

namespace input {

bool
TextInput::pressed(int key) {
  if (m_bindings.pressed(key)) {
    return true;

  } else if (key >= 0x20 && key < 0x7F) {
    Base::insert(m_pos++, 1, key);

  } else {
    switch (key) {
      case 0x7F:
      case 'h' - 'a' + 1: // ^H
      case KEY_BACKSPACE:
        if (m_pos != 0)
          Base::erase(--m_pos, 1);

        break;

      case KEY_DC:
        if (m_pos != size())
          Base::erase(m_pos, 1);

        break;

      case 0x02:
      case KEY_LEFT:
        if (m_pos != 0)
          --m_pos;

        break;

      case 0x06:
      case KEY_RIGHT:
        if (m_pos != size())
          ++m_pos;

        break;

      case KEY_HOME:
        m_pos = 0;
        break;

      case KEY_END:
        m_pos = size();
        break;

      case 'u' - 'a' + 1: // ^U
        Base::erase(0, m_pos);
        m_pos = 0;
        break;

      case 'k' - 'a' + 1: // ^K
        Base::erase(m_pos, size() - m_pos);
        break;

      default:
        return false;
    }
  }

  mark_dirty();

  return true;
}

}
