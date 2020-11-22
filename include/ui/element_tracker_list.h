// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_UI_ELEMENT_TRACKER_LIST_H
#define RTORRENT_UI_ELEMENT_TRACKER_LIST_H

#include "core/download.h"
#include "ui/element_base.h"

class Control;

namespace display {
class WindowTrackerList;
}

namespace ui {

class ElementTrackerList : public ElementBase {
public:
  typedef display::WindowTrackerList WTrackerList;

  ElementTrackerList(core::Download* d);

  void activate(display::Frame* frame, bool focus = true);
  void disable();

  display::Window* window();

private:
  void receive_next();
  void receive_prev();

  void receive_disable();

  void receive_cycle_group();

  core::Download* m_download;
  WTrackerList*   m_window;

  // Change to unsigned, please.
  unsigned int m_focus;
};

}

#endif
