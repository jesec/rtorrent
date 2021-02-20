// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_UI_ELEMENT_STRING_LIST_H
#define RTORRENT_UI_ELEMENT_STRING_LIST_H

#include <algorithm>
#include <functional>
#include <list>
#include <string>
#include <torrent/utils/log.h>

#include "display/window_string_list.h"
#include "ui/element_base.h"

class Control;

namespace ui {

class ElementStringList : public ElementBase {
public:
  using WStringList = display::WindowStringList;
  using List        = std::list<std::string>;

  void activate(display::Frame* frame, bool focus = true) override;
  void disable() override;

  display::Window* window() {
    return m_window;
  }

  template<typename InputIter>
  void set_range(InputIter first, InputIter last) {
    m_list.clear();

    while (first != last)
      m_list.push_back(*(first++));

    if (m_window != nullptr) {
      lt_log_print(torrent::LOG_UI_EVENTS,
                   "element_string_list: set range (visible)");

      m_window->set_range(m_list.begin(), m_list.end());
      m_window->mark_dirty();
    } else {
      lt_log_print(torrent::LOG_UI_EVENTS,
                   "element_string_list: set range (hidden)");
    }
  }

  // A hack, clean this up.
  template<typename InputIter>
  void set_range_dirent(InputIter first, InputIter last) {
    m_list.clear();

    while (first != last)
      m_list.push_back((first++)->d_name);

    if (m_window != nullptr) {
      lt_log_print(torrent::LOG_UI_EVENTS,
                   "element_string_list: set dirent range (visible)");

      m_window->set_range(m_list.begin(), m_list.end());
      m_window->mark_dirty();
    } else {
      lt_log_print(torrent::LOG_UI_EVENTS,
                   "element_string_list: set dirent range (hidden)");
    }
  }

  void next_screen();

private:
  WStringList* m_window{ nullptr };
  List         m_list;
};

}

#endif
