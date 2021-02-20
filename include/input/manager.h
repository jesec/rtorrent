// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_INPUT_MANAGER_H
#define RTORRENT_INPUT_MANAGER_H

#include <vector>

namespace input {

class Bindings;
class TextInput;

class Manager : private std::vector<Bindings*> {
public:
  using Base = std::vector<Bindings*>;

  using Base::const_iterator;
  using Base::const_reverse_iterator;
  using Base::iterator;
  using Base::reverse_iterator;

  using Base::begin;
  using Base::end;
  using Base::rbegin;
  using Base::rend;

  using Base::push_back;

  void erase(Bindings* b);

  void pressed(int key);

  void set_text_input(TextInput* input = nullptr) {
    m_textInput = input;
  }

private:
  TextInput* m_textInput{ nullptr };
};

}

#endif
