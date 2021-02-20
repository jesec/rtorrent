// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_DISPLAY_TEXT_ELEMENT_H
#define RTORRENT_DISPLAY_TEXT_ELEMENT_H

#include <cinttypes>
#include <vector>

#include "display/canvas.h"
#include "rpc/command_map.h"

namespace display {

class TextElement {
public:
  using extent_type = uint32_t;

  static constexpr extent_type extent_full = ~extent_type();

  TextElement()                   = default;
  virtual ~TextElement()          = default;
  TextElement(const TextElement&) = delete;
  void operator=(const TextElement&) = delete;

  // The last element must point to a valid memory location into which
  // the caller must write a '\0' to terminate the c string. The
  // attributes must contain at least one attribute.
  virtual char* print(char*                    first,
                      char*                    last,
                      Canvas::attributes_list* attributes,
                      rpc::target_type         target) = 0;

  virtual extent_type max_length() = 0;

  static void push_attribute(Canvas::attributes_list* attributes,
                             Attributes               value);
};

}

#endif
