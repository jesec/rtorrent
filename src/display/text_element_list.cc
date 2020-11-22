// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#include "config.h"

#include <algorithm>
#include <torrent/exceptions.h>
#include <torrent/utils/functional.h>

#include "text_element_list.h"

namespace display {

void
TextElementList::clear() {
  std::for_each(begin(), end(), torrent::utils::call_delete<TextElement>());
  base_type::clear();
}

char*
TextElementList::print(char*                    first,
                       char*                    last,
                       Canvas::attributes_list* attributes,
                       rpc::target_type         target) {
  int column = m_columnWidth != NULL ? m_column : 0;

  // Call print for each element even if first == last so that any
  // attributes gets added to the list.
  for (iterator itr = begin(); itr != end(); ++itr)
    if (column-- > 0) {
      char* columnEnd = std::min(last, first + *m_columnWidth);

      if (columnEnd < first || columnEnd > last)
        throw torrent::internal_error(
          "TextElementList::print(...) columnEnd < first || columnEnd > last.");

      first = (*itr)->print(first, columnEnd, attributes, target);

      if (first > columnEnd)
        throw torrent::internal_error(
          "TextElementList::print(...) first > columnEnd.");

      std::memset(first, ' ', columnEnd - first);
      first = columnEnd;

    } else {
      first = (*itr)->print(first, last, attributes, target);
    }

  return first;
}

TextElementList::extent_type
TextElementList::max_length() {
  extent_type length = 0;
  int         column = m_columnWidth != NULL ? m_column : 0;

  for (iterator itr = begin(); itr != end(); ++itr) {
    extent_type l = column-- > 0
                      ? std::min((*itr)->max_length(), *m_columnWidth)
                      : (*itr)->max_length();

    if (l == extent_full)
      return extent_full;

    length += l;
  }

  return length;
}

}
