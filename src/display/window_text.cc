// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#include "config.h"

#include <algorithm>
#include <torrent/utils/functional.h>

#include "display/canvas.h"
#include "display/utils.h"

#include "display/window_text.h"

namespace display {

WindowText::WindowText(rpc::target_type target, extent_type margin)
  : Window(new Canvas, 0, 0, 0, extent_static, extent_static)
  , m_target(target)
  , m_errorHandler(NULL)
  , m_margin(margin)
  , m_interval(0) {}

void
WindowText::clear() {
  std::for_each(begin(), end(), torrent::utils::call_delete<TextElement>());
  base_type::clear();

  delete m_errorHandler;
  m_errorHandler = NULL;
}

void
WindowText::push_back(TextElement* element) {
  base_type::push_back(element);

  //   m_minHeight = size();
  m_maxHeight = size();

  if (element != NULL) {
    extent_type width = element->max_length();

    if (width == extent_full)
      m_maxWidth = extent_full;
    else
      m_maxWidth = std::max(m_maxWidth, element->max_length() + m_margin);
  }

  // Check if active, if so do the update thingie. Or be lazy?
}

void
WindowText::redraw() {
  if (m_interval != 0)
    m_slotSchedule(
      this,
      (cachedTime + torrent::utils::timer::from_seconds(m_interval))
        .round_seconds());

  m_canvas->erase();

  unsigned int position = 0;

  if (m_canvas->height() == 0)
    return;

  if (m_errorHandler != NULL && m_target.second == NULL) {
    char buffer[m_canvas->width() + 1];

    Canvas::attributes_list attributes;
    attributes.push_back(
      Attributes(buffer, Attributes::a_normal, Attributes::color_default));

    char* last = m_errorHandler->print(
      buffer, buffer + m_canvas->width(), &attributes, m_target);

    m_canvas->print_attributes(0, position, buffer, last, &attributes);
    return;
  }

  for (iterator itr = begin(); itr != end() && position < m_canvas->height();
       ++itr, ++position) {
    if (*itr == NULL)
      continue;

    char buffer[m_canvas->width() + 1];

    Canvas::attributes_list attributes;
    attributes.push_back(
      Attributes(buffer, Attributes::a_normal, Attributes::color_default));

    char* last =
      (*itr)->print(buffer, buffer + m_canvas->width(), &attributes, m_target);

    m_canvas->print_attributes(0, position, buffer, last, &attributes);
  }
}

}
