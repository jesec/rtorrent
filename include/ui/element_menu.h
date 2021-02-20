// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_UI_ELEMENT_MENU_H
#define RTORRENT_UI_ELEMENT_MENU_H

#include "core/download.h"
#include "ui/element_base.h"

namespace display {
class WindowText;
class TextElementStringBase;
}

namespace ui {

struct ElementMenuEntry {
  display::TextElementStringBase* m_element;

  std::function<void()> m_slotFocus;
  std::function<void()> m_slotSelect;
};

class ElementMenu
  : public ElementBase
  , public std::vector<ElementMenuEntry> {
public:
  using base_type = std::vector<ElementMenuEntry>;

  using WindowText = display::WindowText;

  using size_type = uint32_t;

  using value_type       = base_type::value_type;
  using reference        = base_type::reference;
  using iterator         = base_type::iterator;
  using const_iterator   = base_type::const_iterator;
  using reverse_iterator = base_type::reverse_iterator;

  using base_type::empty;
  using base_type::size;

  static constexpr size_type entry_invalid = ~size_type();

  ElementMenu();
  ~ElementMenu() override;

  void activate(display::Frame* frame, bool focus = false) override;
  void disable() override;

  // Consider returning a pointer that can be used to manipulate
  // entries, f.ex disabling them.

  // The c string is not copied nor freed, so it should be constant.
  void push_back(const char*      name,
                 const slot_type& slotSelect = slot_type(),
                 const slot_type& slotFocus  = slot_type());

  void entry_next();
  void entry_prev();

  void entry_select();

  void set_entry(size_type idx, bool triggerSlot);
  void set_entry_trigger(size_type idx) {
    set_entry(idx, true);
  }

private:
  void focus_entry(size_type idx);
  void unfocus_entry(size_type idx);

  WindowText* m_window;

  size_type m_entry;
};

}

#endif
