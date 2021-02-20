// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_DISPLAY_WINDOW_LOG_H
#define RTORRENT_DISPLAY_WINDOW_LOG_H

#include <torrent/utils/log_buffer.h>

#include "display/window.h"

namespace display {

class WindowLog : public Window {
public:
  using iterator = torrent::log_buffer::const_iterator;

  WindowLog(torrent::log_buffer* l);
  ~WindowLog() override;

  void redraw() override;

  void receive_update();

private:
  inline iterator find_older();

  torrent::log_buffer*          m_log;
  torrent::utils::priority_item m_taskUpdate;
};

}

#endif
