// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_DISPLAY_TEXT_ELEMENT_LIST_H
#define RTORRENT_DISPLAY_TEXT_ELEMENT_LIST_H

#include "display/text_element.h"

namespace display {

class TextElementList
  : public TextElement
  , public std::vector<TextElement*> {
public:
  using base_type = std::vector<TextElement*>;

  using value_type       = base_type::value_type;
  using reference        = base_type::reference;
  using iterator         = base_type::iterator;
  using const_iterator   = base_type::const_iterator;
  using reverse_iterator = base_type::reverse_iterator;

  using base_type::empty;
  using base_type::size;

  using base_type::begin;
  using base_type::end;
  using base_type::rbegin;
  using base_type::rend;

  using base_type::push_back;

  ~TextElementList() override {
    clear();
  }

  void clear();

  void set_column(unsigned int column) {
    m_column = column;
  }
  void set_column_width(extent_type* width) {
    m_columnWidth = width;
  }

  char* print(char*                    first,
              char*                    last,
              Canvas::attributes_list* attributes,
              rpc::target_type         target) override;

  extent_type max_length() override;

private:
  unsigned int m_column{ 0 };
  extent_type* m_columnWidth{ nullptr };
};

}

#endif
