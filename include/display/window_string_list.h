// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_DISPLAY_WINDOW_STRING_LIST_H
#define RTORRENT_DISPLAY_WINDOW_STRING_LIST_H

#include <list>
#include <string>

#include "display/window.h"

namespace display {

class WindowStringList : public Window {
public:
  typedef std::list<std::string>::iterator iterator;

  WindowStringList();
  ~WindowStringList();

  iterator get_draw_end() {
    return m_drawEnd;
  }

  void set_range(iterator first, iterator last) {
    m_first = m_drawEnd = first;
    m_last              = last;
  }

  virtual void redraw();

private:
  iterator m_first;
  iterator m_last;

  iterator m_drawEnd;
};

}

#endif
