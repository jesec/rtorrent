// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_DISPLAY_WINDOW_STATUSBAR_H
#define RTORRENT_DISPLAY_WINDOW_STATUSBAR_H

#include <cstdint>

#include "display/window.h"

namespace display {

class WindowStatusbar : public Window {
public:
  WindowStatusbar()
    : Window(new Canvas, 0, 0, 1, extent_full, extent_static) {}

  void redraw() override;

private:
  uint64_t m_lastTick{ 0 };
};

}

#endif
