// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#include "display/canvas.h"
#include "display/utils.h"

#include "display/window_string_list.h"

namespace display {

WindowStringList::WindowStringList()
  : Window(new Canvas, 0, 0, 0, extent_full, extent_full) {}

void
WindowStringList::redraw() {
  m_canvas->erase();

  size_t ypos  = 0;
  size_t xpos  = 1;
  size_t count = 0;

  iterator itr = m_first;

  const auto height = m_canvas->height();
  const auto width  = m_canvas->width();

  while (itr != m_last) {
    if (ypos == height) {
      ypos = 0;
      xpos += count + 2;

      if (xpos + 20 >= width)
        break;

      count = 0;
    }

    count = std::max(itr->size(), count);

    if (xpos + itr->size() <= width)
      m_canvas->print(xpos, ypos++, "%s", itr->c_str());
    else
      m_canvas->print(xpos, ypos++, "%s", itr->substr(0, width - xpos).c_str());

    ++itr;
  }

  m_drawEnd = itr;
}

}
