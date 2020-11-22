// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#include "config.h"

#include <torrent/exceptions.h>

#include "control.h"
#include "display/frame.h"
#include "display/text_element_list.h"
#include "display/window_text.h"
#include "input/manager.h"

#include "ui/element_text.h"

namespace ui {

ElementText::ElementText(rpc::target_type target)
  : m_window(new WindowText(target))
  , m_column(0)
  , m_columnWidth(0) {

  // Move bindings into a function that defines default bindings.
  m_bindings[KEY_LEFT] = m_bindings['B' - '@'] =
    std::bind(&slot_type::operator(), &m_slot_exit);

  //   m_bindings[KEY_UP]    = std::bind(this, &ElementText::entry_prev);
  //   m_bindings[KEY_DOWN]  = std::bind(this, &ElementText::entry_next);
  //   m_bindings[KEY_RIGHT] = m_bindings['F' - '@'] = std::bind(this,
  //   &ElementText::entry_select);
}

ElementText::~ElementText() {
  delete m_window;
}

void
ElementText::activate(display::Frame* frame, bool focus) {
  if (is_active())
    throw torrent::internal_error(
      "ui::ElementText::activate(...) is_active().");

  if (focus)
    control->input()->push_back(&m_bindings);

  m_focus = focus;

  m_frame = frame;
  m_frame->initialize_window(m_window);

  m_window->set_active(true);
}

void
ElementText::disable() {
  if (!is_active())
    throw torrent::internal_error(
      "ui::ElementText::disable(...) !is_active().");

  control->input()->erase(&m_bindings);

  m_frame->clear();
  m_frame = NULL;

  m_window->set_active(false);
}

void
ElementText::push_back(text_element_wrapper entry) {
  m_window->push_back(entry.m_element);

  // For the moment, don't bother doing anything if the window is
  // already active.
  m_window->mark_dirty();
}

void
ElementText::push_column(text_element_wrapper entry1,
                         text_element_wrapper entry2) {
  m_columnWidth = std::max(entry1.m_element->max_length(), m_columnWidth);

  display::TextElementList* list = new display::TextElementList;
  list->set_column(m_column);
  list->set_column_width(&m_columnWidth);

  list->push_back(entry1.m_element);
  list->push_back(entry2.m_element);

  push_back(list);
}

void
ElementText::push_column(text_element_wrapper entry1,
                         text_element_wrapper entry2,
                         text_element_wrapper entry3) {
  m_columnWidth = std::max(entry1.m_element->max_length(), m_columnWidth);

  display::TextElementList* list = new display::TextElementList;
  list->set_column(m_column);
  list->set_column_width(&m_columnWidth);

  list->push_back(entry1.m_element);
  list->push_back(entry2.m_element);
  list->push_back(entry3.m_element);

  push_back(list);
}

void
ElementText::push_column(text_element_wrapper entry1,
                         text_element_wrapper entry2,
                         text_element_wrapper entry3,
                         text_element_wrapper entry4) {
  m_columnWidth = std::max(entry1.m_element->max_length(), m_columnWidth);

  display::TextElementList* list = new display::TextElementList;
  list->set_column(m_column);
  list->set_column_width(&m_columnWidth);

  list->push_back(entry1.m_element);
  list->push_back(entry2.m_element);
  list->push_back(entry3.m_element);
  list->push_back(entry4.m_element);

  push_back(list);
}

void
ElementText::push_column(text_element_wrapper entry1,
                         text_element_wrapper entry2,
                         text_element_wrapper entry3,
                         text_element_wrapper entry4,
                         text_element_wrapper entry5) {
  m_columnWidth = std::max(entry1.m_element->max_length(), m_columnWidth);

  display::TextElementList* list = new display::TextElementList;
  list->set_column(m_column);
  list->set_column_width(&m_columnWidth);

  list->push_back(entry1.m_element);
  list->push_back(entry2.m_element);
  list->push_back(entry3.m_element);
  list->push_back(entry4.m_element);
  list->push_back(entry5.m_element);

  push_back(list);
}

void
ElementText::push_column(text_element_wrapper entry1,
                         text_element_wrapper entry2,
                         text_element_wrapper entry3,
                         text_element_wrapper entry4,
                         text_element_wrapper entry5,
                         text_element_wrapper entry6) {
  m_columnWidth = std::max(entry1.m_element->max_length(), m_columnWidth);

  display::TextElementList* list = new display::TextElementList;
  list->set_column(m_column);
  list->set_column_width(&m_columnWidth);

  list->push_back(entry1.m_element);
  list->push_back(entry2.m_element);
  list->push_back(entry3.m_element);
  list->push_back(entry4.m_element);
  list->push_back(entry5.m_element);
  list->push_back(entry6.m_element);

  push_back(list);
}

}
