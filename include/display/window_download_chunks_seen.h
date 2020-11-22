// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_DISPLAY_WINDOW_DOWNLOAD_CHUNKS_SEEN_H
#define RTORRENT_DISPLAY_WINDOW_DOWNLOAD_CHUNKS_SEEN_H

#include <list>

#include "display/window.h"

namespace core {
class Download;
}

namespace display {

class WindowDownloadChunksSeen : public Window {
public:
  WindowDownloadChunksSeen(core::Download* d, unsigned int* focus);

  virtual void redraw();

  unsigned int rows() const;
  unsigned int chunks_per_row() const {
    return (width() - 6) / 11 * 10;
  }

  unsigned int max_focus() const {
    return std::max<int>(rows() - height() / 2 + 1, 0);
  }

private:
  core::Download* m_download;

  unsigned int* m_focus;
};

}

#endif
