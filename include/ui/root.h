// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_UI_ROOT_H
#define RTORRENT_UI_ROOT_H

#include <cstdint>

#include "input/bindings.h"
#include "ui/download_list.h"

class Control;

namespace display {
class Frame;
class WindowTitle;
class WindowHttpQueue;
class WindowInput;
class WindowStatusbar;
}

namespace input {
class TextInput;
}

namespace ui {

class DownloadList;

using ThrottleNameList = std::vector<std::string>;

class Root {
public:
  using WTitle     = display::WindowTitle;
  using WHttpQueue = display::WindowHttpQueue;
  using WInput     = display::WindowInput;
  using WStatusbar = display::WindowStatusbar;

  using InputHistoryPointers = std::map<int, int>;
  using InputHistoryCategory = std::vector<std::string>;
  using InputHistory         = std::map<int, InputHistoryCategory>;

  Root();

  void init(Control* c);
  void cleanup();

  WTitle* window_title() {
    return m_windowTitle;
  }
  WStatusbar* window_statusbar() {
    return m_windowStatusbar;
  }
  WInput* window_input() {
    return m_windowInput;
  }

  DownloadList* download_list() {
    return m_downloadList;
  }

  void set_down_throttle(unsigned int throttle);
  void set_up_throttle(unsigned int throttle);

  // Rename to raw or something, make base function.
  void set_down_throttle_i64(int64_t throttle) {
    set_down_throttle(throttle >> 10);
  }
  void set_up_throttle_i64(int64_t throttle) {
    set_up_throttle(throttle >> 10);
  }

  void adjust_down_throttle(int throttle);
  void adjust_up_throttle(int throttle);

  const char* get_throttle_keys();

  ThrottleNameList& get_status_throttle_up_names() {
    return m_throttle_up_names;
  }
  ThrottleNameList& get_status_throttle_down_names() {
    return m_throttle_down_names;
  }

  void set_status_throttle_up_names(const ThrottleNameList& throttle_list) {
    m_throttle_up_names = throttle_list;
  }
  void set_status_throttle_down_names(const ThrottleNameList& throttle_list) {
    m_throttle_down_names = throttle_list;
  }

  void enable_input(const std::string&      title,
                    input::TextInput*       input,
                    ui::DownloadList::Input type);
  void disable_input();

  input::TextInput* current_input();

  int get_input_history_size() {
    return m_input_history_length;
  }
  void set_input_history_size(int size);
  void add_to_input_history(ui::DownloadList::Input type, std::string item);

  void load_input_history();
  void save_input_history();
  void clear_input_history();

private:
  void setup_keys();

  Control*      m_control{ nullptr };
  DownloadList* m_downloadList{ nullptr };

  WTitle*     m_windowTitle{ nullptr };
  WHttpQueue* m_windowHttpQueue{ nullptr };
  WInput*     m_windowInput{ nullptr };
  WStatusbar* m_windowStatusbar{ nullptr };

  input::Bindings m_bindings;

  int                  m_input_history_length{ 99 };
  std::string          m_input_history_last_input{ "" };
  int                  m_input_history_pointer_get{ 0 };
  InputHistory         m_input_history;
  InputHistoryPointers m_input_history_pointers;

  void prev_in_input_history(ui::DownloadList::Input type);
  void next_in_input_history(ui::DownloadList::Input type);

  void reset_input_history_attributes(ui::DownloadList::Input type);

  ThrottleNameList m_throttle_up_names;
  ThrottleNameList m_throttle_down_names;
};

}

#endif
