// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_INPUT_PATH_INPUT_H
#define RTORRENT_INPUT_PATH_INPUT_H

#include <functional>
#include <list>

#include "input/text_input.h"
#include "utils/directory.h"

namespace input {

class PathInput : public TextInput {
public:
  typedef utils::Directory::iterator              directory_itr;
  typedef std::pair<directory_itr, directory_itr> range_type;

  typedef std::function<void()>                             slot_void;
  typedef std::function<void(directory_itr, directory_itr)> slot_itr_itr;
  typedef std::list<slot_void>                              signal_void;
  typedef std::list<slot_itr_itr>                           signal_itr_itr;

  PathInput();
  virtual ~PathInput() {}

  signal_void& signal_show_next() {
    return m_signal_show_next;
  }
  signal_itr_itr& signal_show_range() {
    return m_signal_show_range;
  }

  virtual bool pressed(int key);

private:
  void receive_do_complete();

  size_type  find_last_delim();
  range_type find_incomplete(utils::Directory& d, const std::string& f);

  bool m_showNext;

  signal_void    m_signal_show_next;
  signal_itr_itr m_signal_show_range;
};

}

#endif
