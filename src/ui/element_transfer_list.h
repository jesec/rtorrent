// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_UI_ELEMENT_TRANSFER_LIST_H
#define RTORRENT_UI_ELEMENT_TRANSFER_LIST_H

#include "core/download.h"

#include "element_base.h"

class Control;

namespace display {
class WindowDownloadTransferList;
}

namespace ui {

class ElementTransferList : public ElementBase {
public:
  typedef display::WindowDownloadTransferList WTransferList;

  ElementTransferList(core::Download* d);

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
  WTransferList*  m_window;

  unsigned int m_focus;
};

}

#endif
