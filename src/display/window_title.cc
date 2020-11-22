// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#include "config.h"

#include "display/canvas.h"

#include "display/window_title.h"

namespace display {

void
WindowTitle::redraw() {
  m_slotSchedule(
    this,
    (cachedTime + torrent::utils::timer::from_seconds(1)).round_seconds());
  m_canvas->erase();

  m_canvas->print(
    std::max(0, ((int)m_canvas->width() - (int)m_title.size()) / 2 - 4),
    0,
    "*** %s ***",
    m_title.c_str());
}

}
