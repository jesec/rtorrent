// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#include "config.h"

#include "display/canvas.h"
#include "input/text_input.h"

#include "display/window_input.h"

namespace display {

void
WindowInput::redraw() {
  m_canvas->erase();
  m_canvas->print(0,
                  0,
                  "%s> %s",
                  m_title.c_str(),
                  m_input != NULL ? m_input->c_str() : "<NULL>");

  if (m_focus)
    m_canvas->set_attr(
      m_input->get_pos() + 2 + m_title.size(), 0, 1, A_REVERSE, COLOR_PAIR(0));
}

}
