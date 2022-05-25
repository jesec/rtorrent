// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#include <stdexcept>

#include "display/window.h"

namespace display {

Window::SlotTimer  Window::m_slotSchedule;
Window::SlotWindow Window::m_slotUnschedule;
Window::Slot       Window::m_slotAdjust;

// When constructing the window we set flag_offscreen so that redraw
// doesn't get triggered until after a successful Frame::balance call.

Window::Window(Canvas*     canvas,
               int         flags,
               extent_type minWidth,
               extent_type minHeight,
               extent_type maxWidth,
               extent_type maxHeight)
  : m_canvas(canvas)
  , m_flags(flags | flag_offscreen)
  ,

  m_minWidth(minWidth)
  , m_minHeight(minHeight)
  ,

  m_maxWidth(maxWidth)
  , m_maxHeight(maxHeight) {

  m_taskUpdate.slot() = [this] { redraw(); };
}

Window::~Window() {
  if (is_active())
    m_slotUnschedule(this);

  delete m_canvas;
}

void
Window::set_active(bool state) {
  if (state == is_active())
    return;

  if (state) {
    // Set offscreen so we don't try rendering before Frame::balance
    // has been called.
    m_flags |= flag_active | flag_offscreen;
    mark_dirty();

  } else {
    m_flags &= ~flag_active;
    m_slotUnschedule(this);
  }
}

void
Window::resize(int x, int y, int w, int h) {
  if (x < 0 || y < 0)
    throw std::logic_error("Window::resize(...) bad x or y position");

  if (w <= 0 || h <= 0)
    throw std::logic_error("Window::resize(...) bad size");

  m_canvas->resize(x, y, w, h);
}

}
