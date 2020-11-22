// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_DISPLAY_MANAGER_H
#define RTORRENT_DISPLAY_MANAGER_H

#include <list>
#include <torrent/utils/priority_queue_default.h>

#include "display/frame.h"

namespace display {

class Window;

class Manager {
public:
  Manager();
  ~Manager();

  void force_redraw();

  void schedule(Window* w, torrent::utils::timer t);
  void unschedule(Window* w);

  void adjust_layout();
  void receive_update();

  // New interface.
  Frame* root_frame() {
    return &m_rootFrame;
  }

private:
  void schedule_update(uint32_t minInterval);

  bool                  m_forceRedraw;
  torrent::utils::timer m_timeLastUpdate;

  torrent::utils::priority_queue_default m_scheduler;
  torrent::utils::priority_item          m_taskUpdate;

  // New interface.
  Frame m_rootFrame;
};

}

#endif
