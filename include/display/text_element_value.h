// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_DISPLAY_TEXT_ELEMENT_VALUE_H
#define RTORRENT_DISPLAY_TEXT_ELEMENT_VALUE_H

#include <cstring>

#include "display/text_element.h"

namespace display {

class TextElementValueBase : public TextElement {
public:
  static constexpr int flag_normal = 0;
  static constexpr int flag_timer  = (1 << 0);
  static constexpr int flag_date   = (1 << 1);
  static constexpr int flag_time   = (1 << 2);

  static constexpr int flag_kb = (1 << 3);
  static constexpr int flag_mb = (1 << 4);
  static constexpr int flag_xb = (1 << 5);

  static constexpr int flag_elapsed   = (1 << 8);
  static constexpr int flag_remaining = (1 << 9);
  static constexpr int flag_usec      = (1 << 10);

  int flags() const {
    return m_flags;
  }
  void set_flags(int flags) {
    m_flags = flags;
  }

  int attributes() const {
    return m_attributes;
  }
  void set_attributes(int a) {
    m_attributes = a;
  }

  char* print(char*                    first,
              char*                    last,
              Canvas::attributes_list* attributes,
              rpc::target_type         target) override;

protected:
  virtual int64_t value(void* object) = 0;

  int m_flags;
  int m_attributes;
};

class TextElementValue : public TextElementValueBase {
public:
  TextElementValue(int64_t value,
                   int     flags      = flag_normal,
                   int     attributes = Attributes::a_invalid)
    : m_value(value) {
    m_flags      = flags;
    m_attributes = attributes;
  }

  int64_t value() const {
    return m_value;
  }
  void set_value(int64_t v) {
    m_value = v;
  }

  extent_type max_length() override {
    return 12;
  }

private:
  int64_t value(void*) override {
    return m_value;
  }

  int64_t m_value;
};

template<typename slot_type>
class TextElementValueSlot0 : public TextElementValueBase {
public:
  using result_type = typename slot_type::result_type;

  TextElementValueSlot0(const slot_type& slot,
                        int              flags      = flag_normal,
                        int              attributes = Attributes::a_invalid)
    : m_slot(slot) {
    m_flags      = flags;
    m_attributes = attributes;
  }

  extent_type max_length() override {
    return 12;
  }

private:
  int64_t value(void*) override {
    return m_slot();
  }

  slot_type m_slot;
};

template<typename slot_type>
class TextElementValueSlot : public TextElementValueBase {
public:
  using arg1_type   = typename slot_type::argument_type;
  using result_type = typename slot_type::result_type;

  TextElementValueSlot(const slot_type& slot,
                       int              flags      = flag_normal,
                       int              attributes = Attributes::a_invalid)
    : m_slot(slot) {
    m_flags      = flags;
    m_attributes = attributes;
  }

  extent_type max_length() override {
    return 12;
  }

private:
  int64_t value(void* object) override {
    if (object == nullptr)
      return 0;

    return m_slot(reinterpret_cast<arg1_type>(object));
  }

  slot_type m_slot;
};

template<typename slot_type>
inline TextElementValueSlot0<slot_type>*
text_element_value_void(const slot_type& slot,
                        int flags      = TextElementValueBase::flag_normal,
                        int attributes = Attributes::a_invalid) {
  return new TextElementValueSlot0<slot_type>(slot, flags, attributes);
}

template<typename slot_type>
inline TextElementValueSlot<slot_type>*
text_element_value_slot(const slot_type& slot,
                        int flags      = TextElementValueBase::flag_normal,
                        int attributes = Attributes::a_invalid) {
  return new TextElementValueSlot<slot_type>(slot, flags, attributes);
}

}

#endif
