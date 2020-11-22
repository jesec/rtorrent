// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#include <algorithm>

#include "input/bindings.h"

namespace input {

bool
Bindings::pressed(int key) {
  if (!m_enabled)
    return false;

  const_iterator itr = find(key);

  if (itr == end())
    return false;

  itr->second();
  return true;
}

}
