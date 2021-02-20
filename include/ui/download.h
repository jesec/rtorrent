// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_UI_DOWNLOAD_H
#define RTORRENT_UI_DOWNLOAD_H

#include <list>
#include <torrent/peer/peer.h>

#include "display/manager.h"
#include "ui/element_base.h"
#include "utils/list_focus.h"

namespace display {
class WindowDownloadStatusbar;
}

namespace core {
class Download;
}

namespace ui {

class Download : public ElementBase {
public:
  using WDownloadStatus = display::WindowDownloadStatusbar;

  using PList = std::list<torrent::Peer>;

  using Display = enum {
    DISPLAY_MENU,
    DISPLAY_PEER_LIST,
    DISPLAY_INFO,
    DISPLAY_FILE_LIST,
    DISPLAY_TRACKER_LIST,
    DISPLAY_CHUNKS_SEEN,
    DISPLAY_TRANSFER_LIST,
    DISPLAY_MAX_SIZE
  };

  Download(core::Download* d);
  ~Download() override;
  Download(const Download&) = delete;
  void operator=(const Download&) = delete;

  void activate(display::Frame* frame, bool focus = true) override;
  void disable() override;

  void activate_display(Display d, bool focusDisplay);

  void activate_display_focus(Display d) {
    activate_display(d, true);
  }
  void activate_display_menu(Display d) {
    activate_display(d, false);
  }

  void receive_next_priority();
  void receive_prev_priority();

  void adjust_up_throttle(int throttle);
  void adjust_down_throttle(int throttle);

  display::Window* window() {
    return nullptr;
  }
  core::Download* download() {
    return m_download;
  };

private:
  inline ElementBase* create_menu();
  inline ElementBase* create_info();

  void receive_min_uploads(int t);
  void receive_max_uploads(int t);
  void receive_min_downloads(int t);
  void receive_max_downloads(int t);
  void receive_min_peers(int t);
  void receive_max_peers(int t);

  void bind_keys();

  core::Download* m_download;

  Display      m_state;
  ElementBase* m_uiArray[DISPLAY_MAX_SIZE];

  bool m_focusDisplay;

  WDownloadStatus* m_windowDownloadStatus;
};

}

#endif
