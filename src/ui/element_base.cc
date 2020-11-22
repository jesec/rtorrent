// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#include "config.h"

#include <torrent/exceptions.h>

#include "display/frame.h"
#include "display/window.h"

#include "element_base.h"

namespace ui {

void
ElementBase::mark_dirty() {
  if (is_active())
    m_frame->window()->mark_dirty();
}

}
