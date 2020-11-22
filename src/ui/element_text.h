// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_UI_ELEMENT_TEXT_H
#define RTORRENT_UI_ELEMENT_TEXT_H

#include "core/download.h"
#include "display/text_element_string.h"
#include "display/window_text.h"

#include "element_base.h"

namespace display {
class TextElement;
}

namespace ui {

struct text_element_wrapper;

class ElementText : public ElementBase {
public:
  typedef display::WindowText WindowText;

  typedef uint32_t size_type;
  typedef uint32_t extent_type;

  ElementText(rpc::target_type target);
  ~ElementText();

  rpc::target_type target() const {
    return m_window->target();
  }
  void set_target(rpc::target_type target) {
    m_window->set_target(target);
    m_window->mark_dirty();
  }

  uint32_t interval() const {
    return m_window->interval();
  }
  void set_interval(uint32_t i) {
    m_window->set_interval(i);
    m_window->mark_dirty();
  }

  void activate(display::Frame* frame, bool focus = false);
  void disable();

  void mark_dirty() {
    m_window->mark_dirty();
  }

  // Consider returning a pointer that can be used to manipulate
  // entries, f.ex disabling them.

  void push_back(text_element_wrapper entry);

  void push_column(text_element_wrapper entry1, text_element_wrapper entry2);

  void push_column(text_element_wrapper entry1,
                   text_element_wrapper entry2,
                   text_element_wrapper entry3);

  void push_column(text_element_wrapper entry1,
                   text_element_wrapper entry2,
                   text_element_wrapper entry3,
                   text_element_wrapper entry4);

  void push_column(text_element_wrapper entry1,
                   text_element_wrapper entry2,
                   text_element_wrapper entry3,
                   text_element_wrapper entry4,
                   text_element_wrapper entry5);

  void push_column(text_element_wrapper entry1,
                   text_element_wrapper entry2,
                   text_element_wrapper entry3,
                   text_element_wrapper entry4,
                   text_element_wrapper entry5,
                   text_element_wrapper entry6);

  void set_column(unsigned int column) {
    m_column = column;
  }
  void set_error_handler(display::TextElement* t) {
    m_window->set_error_handler(t);
  }

  extent_type column_width() const {
    return m_columnWidth;
  }
  void set_column_width(extent_type width) {
    m_columnWidth = width;
  }

private:
  WindowText* m_window;

  unsigned int m_column;
  extent_type  m_columnWidth;
};

struct text_element_wrapper {
  text_element_wrapper(const char* cstr)
    : m_element(new display::TextElementCString(cstr)) {}
  text_element_wrapper(display::TextElement* element)
    : m_element(element) {}

  display::TextElement* m_element;
};

}

#endif
