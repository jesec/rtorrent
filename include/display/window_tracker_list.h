// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_DISPLAY_TRACKER_LIST_H
#define RTORRENT_DISPLAY_TRACKER_LIST_H

#include "display/window.h"

namespace core {
class Download;
}

namespace display {

class WindowTrackerList : public Window {
public:
  WindowTrackerList(core::Download* d, unsigned int* focus);

  virtual void redraw();

private:
  core::Download* m_download;

  unsigned int* m_focus;
};

}

#endif
