// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_UI_ELEMENT_CHUNKS_SEEN_H
#define RTORRENT_UI_ELEMENT_CHUNKS_SEEN_H

#include "core/download.h"
#include "ui/element_base.h"

class Control;

namespace display {
class WindowDownloadChunksSeen;
}

namespace ui {

class ElementChunksSeen : public ElementBase {
public:
  typedef display::WindowDownloadChunksSeen WChunksSeen;

  ElementChunksSeen(core::Download* d);

  void activate(display::Frame* frame, bool focus = true);
  void disable();

  display::Window* window();

private:
  //   void                receive_disable();
  void receive_next();
  void receive_prev();
  void receive_pagenext();
  void receive_pageprev();

  core::Download* m_download;
  WChunksSeen*    m_window;

  unsigned int m_focus;
};

}

#endif
