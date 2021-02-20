// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_WINDOW_DOWNLOAD_STATUSBAR_H
#define RTORRENT_WINDOW_DOWNLOAD_STATUSBAR_H

#include "display/window.h"

namespace core {
class Download;
}

namespace display {

class WindowDownloadStatusbar : public Window {
public:
  WindowDownloadStatusbar(core::Download* d);

  void redraw() override;

private:
  core::Download* m_download;
};

}

#endif
