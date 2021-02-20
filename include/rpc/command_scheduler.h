// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_COMMAND_SCHEDULER_H
#define RTORRENT_COMMAND_SCHEDULER_H

#include <cstdint>
#include <string>
#include <vector>

namespace torrent {
class Object;
}

namespace rpc {

class CommandSchedulerItem;

class CommandScheduler : public std::vector<CommandSchedulerItem*> {
public:
  using SlotString = std::function<void(const std::string&)>;
  using Time       = std::pair<int, int>;
  using base_type  = std::vector<CommandSchedulerItem*>;

  using base_type::begin;
  using base_type::end;
  using base_type::value_type;

  ~CommandScheduler();

  void set_slot_error_message(SlotString s) {
    m_slotErrorMessage = s;
  }

  // slot_error_message or something.

  iterator find(const std::string& key);

  // If the key already exists then the old item is deleted. It is
  // safe to call erase on end().
  iterator insert(const std::string& key);
  void     erase(iterator itr);
  void     erase_str(const std::string& key) {
    erase(find(key));
  }

  void parse(const std::string&     key,
             const std::string&     bufAbsolute,
             const std::string&     bufInterval,
             const torrent::Object& command);

  static uint32_t parse_absolute(const char* str);
  static uint32_t parse_interval(const char* str);

  static Time parse_time(const char* str);

private:
  void call_item(value_type item);

  SlotString m_slotErrorMessage = nullptr;
};

}

#endif
