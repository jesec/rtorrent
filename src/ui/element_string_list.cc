// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#include "config.h"

#include <torrent/exceptions.h>

#include "display/frame.h"
#include "input/manager.h"

#include "control.h"
#include "element_string_list.h"

namespace ui {

ElementStringList::ElementStringList()
  : m_window(NULL) {}

void
ElementStringList::activate(display::Frame* frame, bool focus) {
  if (is_active())
    throw torrent::internal_error(
      "ui::ElementStringList::activate(...) is_active().");

  lt_log_print(torrent::LOG_UI_EVENTS, "element_string_list: activate");

  control->input()->push_back(&m_bindings);

  m_window = new WStringList();
  m_window->set_active(true);

  m_frame = frame;
  m_frame->initialize_window(m_window);
}

void
ElementStringList::disable() {
  if (!is_active())
    throw torrent::internal_error(
      "ui::ElementStringList::disable(...) !is_active().");

  lt_log_print(torrent::LOG_UI_EVENTS, "element_string_list: deactivate");

  control->input()->erase(&m_bindings);

  m_frame->clear();
  m_frame = NULL;

  delete m_window;
  m_window = NULL;
}

void
ElementStringList::next_screen() {
  if (m_window == NULL)
    return;

  if (m_window->get_draw_end() != m_list.end())
    m_window->set_range(m_window->get_draw_end(), m_list.end());
  else
    m_window->set_range(m_list.begin(), m_list.end());

  m_window->mark_dirty();
}

}
