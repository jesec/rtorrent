// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#include <torrent/exceptions.h>

#include "control.h"
#include "display/frame.h"
#include "display/window_download_transfer_list.h"
#include "input/manager.h"

#include "ui/element_transfer_list.h"

namespace ui {

ElementTransferList::ElementTransferList(core::Download* d)
  : m_download(d)
  , m_window(nullptr)
  , m_focus(0) {

  m_bindings[KEY_LEFT] = m_bindings['B' - '@'] =
    std::bind(&slot_type::operator(), &m_slot_exit);

  m_bindings[KEY_DOWN] = std::bind(&ElementTransferList::receive_next, this);
  m_bindings[KEY_UP]   = std::bind(&ElementTransferList::receive_prev, this);
  m_bindings[KEY_NPAGE] =
    std::bind(&ElementTransferList::receive_pagenext, this);
  m_bindings[KEY_PPAGE] =
    std::bind(&ElementTransferList::receive_pageprev, this);
}

void
ElementTransferList::activate(display::Frame* frame, bool focus) {
  if (is_active())
    throw torrent::internal_error(
      "ui::ElementTransferList::activate(...) is_active().");

  if (focus)
    control->input()->push_back(&m_bindings);

  m_window = new WTransferList(m_download, &m_focus);
  m_window->set_active(true);

  m_frame = frame;
  m_frame->initialize_window(m_window);
}

void
ElementTransferList::disable() {
  if (!is_active())
    throw torrent::internal_error(
      "ui::ElementTransferList::disable(...) !is_active().");

  control->input()->erase(&m_bindings);

  m_frame->clear();
  m_frame = nullptr;

  delete m_window;
  m_window = nullptr;
}

display::Window*
ElementTransferList::window() {
  return m_window;
}

// void
// ElementTransferList::receive_disable() {
//   if (m_window == NULL)
//     throw std::logic_error("ui::ElementTransferList::receive_disable(...)
//     called on a disabled object");

//   if (m_download->download()->tracker(m_focus).is_enabled())
//     m_download->download()->tracker(m_focus).disable();
//   else
//     m_download->download()->tracker(m_focus).enable();

//   m_window->mark_dirty();
// }

void
ElementTransferList::receive_next() {
  if (m_window == nullptr)
    throw torrent::internal_error(
      "ui::ElementTransferList::receive_next(...) called on a disabled object");

  if (++m_focus > m_window->max_focus())
    m_focus = 0;

  //   m_window->mark_dirty();
}

void
ElementTransferList::receive_prev() {
  if (m_window == nullptr)
    throw torrent::internal_error(
      "ui::ElementTransferList::receive_prev(...) called on a disabled object");

  if (m_focus > 0)
    --m_focus;
  else
    m_focus = m_window->max_focus();

  //   m_window->mark_dirty();
}

void
ElementTransferList::receive_pagenext() {
  if (m_window == nullptr)
    throw torrent::internal_error("ui::ElementTransferList::receive_pagenext(.."
                                  ".) called on a disabled object");

  unsigned int visible    = m_window->height() - 1;
  unsigned int scrollable = std::max<int>(m_window->rows() - visible, 0);

  if (scrollable == 0 || m_focus == scrollable)
    m_focus = 0;
  else if (m_focus + visible / 2 < scrollable)
    m_focus += visible / 2;
  else
    m_focus = scrollable;

  //   m_window->mark_dirty();
}

void
ElementTransferList::receive_pageprev() {
  if (m_window == nullptr)
    throw torrent::internal_error("ui::ElementTransferList::receive_pageprev(.."
                                  ".) called on a disabled object");

  unsigned int visible    = m_window->height() - 1;
  unsigned int scrollable = std::max<int>(m_window->rows() - visible, 0);

  if (m_focus > visible / 2)
    m_focus -= visible / 2;
  else if (scrollable > 0 && m_focus == 0)
    m_focus = scrollable;
  else
    m_focus = 0;

  //   m_window->mark_dirty();
}

}
