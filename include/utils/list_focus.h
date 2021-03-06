// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_UTILS_LIST_FOCUS_H
#define RTORRENT_UTILS_LIST_FOCUS_H

#include <functional>

namespace utils {

// Can't make this class inherit privately due to gcc PR 14258.

template<typename Base>
class ListFocus {
public:
  using base_type   = Base;
  using slot_void   = std::function<void()>;
  using signal_void = std::list<slot_void>;

  using iterator               = typename base_type::iterator;
  using const_iterator         = typename base_type::const_iterator;
  using reverse_iterator       = typename base_type::reverse_iterator;
  using const_reverse_iterator = typename base_type::const_reverse_iterator;

  using value_type = typename base_type::value_type;

  ListFocus(base_type* b = NULL)
    : m_base(b) {
    if (b)
      m_focus = b->end();
  }

  // Convinience functions, would have added more through using, but
  // can't.
  iterator begin() {
    return m_base->begin();
  }
  iterator end() {
    return m_base->end();
  }
  reverse_iterator rbegin() {
    return m_base->rbegin();
  }
  reverse_iterator rend() {
    return m_base->rend();
  }

  // Don't do erase on this object without making sure focus is right.
  base_type& base() {
    return *m_base;
  }

  iterator get_focus() {
    return m_focus;
  }
  void set_focus(iterator itr);

  // These are looping increment/decrements.
  iterator inc_focus();
  iterator dec_focus();

  iterator erase(iterator itr);
  void     remove(const value_type& v);

  // Be careful with copying signals.
  signal_void& signal_changed() {
    return m_signal_changed;
  }

private:
  void emit_changed();

  base_type* m_base;
  iterator   m_focus;

  signal_void m_signal_changed;
};

template<typename Base>
void
ListFocus<Base>::set_focus(iterator itr) {
  m_focus = itr;
  emit_changed();
}

template<typename Base>
typename ListFocus<Base>::iterator
ListFocus<Base>::inc_focus() {
  if (m_focus != end())
    ++m_focus;
  else
    m_focus = begin();

  emit_changed();
  return m_focus;
}

template<typename Base>
typename ListFocus<Base>::iterator
ListFocus<Base>::dec_focus() {
  if (m_focus != begin())
    --m_focus;
  else
    m_focus = end();

  emit_changed();
  return m_focus;
}

template<typename Base>
typename ListFocus<Base>::iterator
ListFocus<Base>::erase(iterator itr) {
  if (itr == m_focus)
    return m_focus = m_base->erase(itr);
  else
    return m_base->erase(itr);

  emit_changed();
}

template<typename Base>
void
ListFocus<Base>::remove(const value_type& v) {
  iterator first = begin();
  iterator last  = end();

  while (first != last)
    if (*first == v)
      first = erase(first);
    else
      ++first;
}

template<typename Base>
void
ListFocus<Base>::emit_changed() {
  for (signal_void::iterator itr  = m_signal_changed.begin(),
                             last = m_signal_changed.end();
       itr != last;
       itr++)
    (*itr)();
}

}

#endif
