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
  using directory_itr = utils::Directory::iterator;
  using range_type    = std::pair<directory_itr, directory_itr>;

  using slot_void      = std::function<void()>;
  using slot_itr_itr   = std::function<void(directory_itr, directory_itr)>;
  using signal_void    = std::list<slot_void>;
  using signal_itr_itr = std::list<slot_itr_itr>;

  ~PathInput() override = default;

  signal_void& signal_show_next() {
    return m_signal_show_next;
  }
  signal_itr_itr& signal_show_range() {
    return m_signal_show_range;
  }

  bool pressed(int key) override;

private:
  void receive_do_complete();

  size_type  find_last_delim();
  range_type find_incomplete(utils::Directory& d, const std::string& f);

  bool m_showNext{ false };

  signal_void    m_signal_show_next;
  signal_itr_itr m_signal_show_range;
};

}

#endif
