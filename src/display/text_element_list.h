// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_DISPLAY_TEXT_ELEMENT_LIST_H
#define RTORRENT_DISPLAY_TEXT_ELEMENT_LIST_H

#include "text_element.h"

namespace display {

class TextElementList
  : public TextElement
  , public std::vector<TextElement*> {
public:
  typedef std::vector<TextElement*> base_type;

  typedef base_type::value_type       value_type;
  typedef base_type::reference        reference;
  typedef base_type::iterator         iterator;
  typedef base_type::const_iterator   const_iterator;
  typedef base_type::reverse_iterator reverse_iterator;

  using base_type::empty;
  using base_type::size;

  using base_type::begin;
  using base_type::end;
  using base_type::rbegin;
  using base_type::rend;

  using base_type::push_back;

  TextElementList()
    : m_column(0)
    , m_columnWidth(0) {}
  virtual ~TextElementList() {
    clear();
  }

  void clear();

  void set_column(unsigned int column) {
    m_column = column;
  }
  void set_column_width(extent_type* width) {
    m_columnWidth = width;
  }

  virtual char* print(char*                    first,
                      char*                    last,
                      Canvas::attributes_list* attributes,
                      rpc::target_type         target);

  virtual extent_type max_length();

private:
  unsigned int m_column;
  extent_type* m_columnWidth;
};

}

#endif
