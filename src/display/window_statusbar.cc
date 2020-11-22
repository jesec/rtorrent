// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#include "config.h"

#include <torrent/rate.h>
#include <torrent/torrent.h>

#include "control.h"
#include "display/canvas.h"
#include "display/utils.h"

#include "display/window_statusbar.h"

namespace display {

void
WindowStatusbar::redraw() {
  m_slotSchedule(
    this,
    (cachedTime + torrent::utils::timer::from_seconds(1)).round_seconds());

  m_canvas->erase();

  // TODO: Make a buffer with size = get_width?
  char  buffer[m_canvas->width() + 1];
  char* position;
  char* last = buffer + m_canvas->width();

  position = print_status_info(buffer, last);
  m_canvas->print(0, 0, "%s", buffer);

  last = last - (position - buffer);

  if (last > buffer) {
    position = print_status_extra(buffer, last);
    m_canvas->print(m_canvas->width() - (position - buffer), 0, "%s", buffer);
  }

  m_lastTick = control->tick();
}

}
