// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#include "config.h"

#include <torrent/exceptions.h>

#include "control.h"
#include "display/frame.h"
#include "display/window_download_chunks_seen.h"
#include "input/manager.h"

#include "ui/element_chunks_seen.h"

namespace ui {

ElementChunksSeen::ElementChunksSeen(core::Download* d)
  : m_download(d)
  , m_window(NULL)
  , m_focus(0) {

  m_bindings[KEY_LEFT] = m_bindings['B' - '@'] =
    std::bind(&slot_type::operator(), &m_slot_exit);

  m_bindings[KEY_DOWN] = m_bindings['N' - '@'] =
    std::bind(&ElementChunksSeen::receive_next, this);
  m_bindings[KEY_UP] = m_bindings['P' - '@'] =
    std::bind(&ElementChunksSeen::receive_prev, this);
  m_bindings[KEY_NPAGE] = std::bind(&ElementChunksSeen::receive_pagenext, this);
  m_bindings[KEY_PPAGE] = std::bind(&ElementChunksSeen::receive_pageprev, this);
}

void
ElementChunksSeen::activate(display::Frame* frame, bool focus) {
  if (is_active())
    throw torrent::internal_error(
      "ui::ElementChunksSeen::activate(...) is_active().");

  if (focus)
    control->input()->push_back(&m_bindings);

  m_window = new WChunksSeen(m_download, &m_focus);
  m_window->set_active(true);

  m_frame = frame;
  m_frame->initialize_window(m_window);
}

void
ElementChunksSeen::disable() {
  if (!is_active())
    throw torrent::internal_error(
      "ui::ElementChunksSeen::disable(...) !is_active().");

  control->input()->erase(&m_bindings);

  m_frame->clear();
  m_frame = NULL;

  delete m_window;
  m_window = NULL;
}

display::Window*
ElementChunksSeen::window() {
  return m_window;
}

// void
// ElementChunksSeen::receive_disable() {
//   if (m_window == NULL)
//     throw std::logic_error("ui::ElementChunksSeen::receive_disable(...)
//     called on a disabled object");

//   if (m_download->download()->tracker(m_focus).is_enabled())
//     m_download->download()->tracker(m_focus).disable();
//   else
//     m_download->download()->tracker(m_focus).enable();

//   m_window->mark_dirty();
// }

void
ElementChunksSeen::receive_next() {
  if (m_window == NULL)
    throw torrent::internal_error(
      "ui::ElementChunksSeen::receive_next(...) called on a disabled object");

  if (++m_focus > m_window->max_focus())
    m_focus = 0;

  m_window->mark_dirty();
}

void
ElementChunksSeen::receive_prev() {
  if (m_window == NULL)
    throw torrent::internal_error(
      "ui::ElementChunksSeen::receive_prev(...) called on a disabled object");

  if (m_focus > 0)
    --m_focus;
  else
    m_focus = m_window->max_focus();

  m_window->mark_dirty();
}

void
ElementChunksSeen::receive_pagenext() {
  if (m_window == NULL)
    throw torrent::internal_error("ui::ElementChunksSeen::receive_pagenext(...)"
                                  " called on a disabled object");

  unsigned int visible  = m_window->height() - 1;
  unsigned int maxFocus = m_window->max_focus();

  if (maxFocus == 0 || m_focus == maxFocus)
    m_focus = 0;
  else if (m_focus + visible / 2 < maxFocus)
    m_focus += visible / 2;
  else
    m_focus = maxFocus;

  m_window->mark_dirty();
}

void
ElementChunksSeen::receive_pageprev() {
  if (m_window == NULL)
    throw torrent::internal_error("ui::ElementChunksSeen::receive_pageprev(...)"
                                  " called on a disabled object");

  unsigned int visible  = m_window->height() - 1;
  unsigned int maxFocus = m_window->max_focus();

  if (m_focus > visible / 2)
    m_focus -= visible / 2;
  else if (maxFocus > 0 && m_focus == 0)
    m_focus = maxFocus;
  else
    m_focus = 0;

  m_window->mark_dirty();
}

}
