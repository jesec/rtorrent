// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#include <algorithm>
#include <functional>
#include <torrent/exceptions.h>

#include "input/bindings.h"
#include "input/text_input.h"

#include "input/manager.h"

namespace input {

void
Manager::erase(Bindings* b) {
  iterator itr = std::find(begin(), end(), b);

  if (itr == end())
    return;

  Base::erase(itr);

  if (std::find(begin(), end(), b) != end())
    throw torrent::internal_error(
      "Manager::erase(...) found duplicate bindings.");
}

void
Manager::pressed(int key) {
  if (m_textInput != nullptr)
    m_textInput->pressed(key);
  else
    std::find_if(
      rbegin(), rend(), [key](Bindings* b) { return b->pressed(key); });
}

}
