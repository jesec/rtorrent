// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_DISPLAY_WINDOW_DOWNLOAD_LIST_H
#define RTORRENT_DISPLAY_WINDOW_DOWNLOAD_LIST_H

#include "window.h"

#include "core/download_list.h"
#include "core/view.h"

namespace display {

class WindowDownloadList : public Window {
public:
  typedef core::View::signal_void::iterator signal_void_itr;

  WindowDownloadList();
  ~WindowDownloadList();

  virtual void redraw();

  void set_view(core::View* l);

private:
  core::View* m_view;

  signal_void_itr m_changed_itr;
};

}

#endif
