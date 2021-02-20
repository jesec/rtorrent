// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_COMMAND_SCHEDULER_ITEM_H
#define RTORRENT_COMMAND_SCHEDULER_ITEM_H

#include <functional>

#include <torrent/object.h>

#include "globals.h"

namespace rpc {

class CommandSchedulerItem {
public:
  using slot_void = std::function<void()>;

  CommandSchedulerItem(const std::string& key)
    : m_key(key)
    , m_interval(0) {}
  ~CommandSchedulerItem();
  CommandSchedulerItem(const CommandSchedulerItem&) = delete;
  void operator=(const CommandSchedulerItem&) = delete;

  bool is_queued() const {
    return m_task.is_queued();
  }

  void enable(torrent::utils::timer t);
  void disable();

  const std::string& key() const {
    return m_key;
  }
  torrent::Object& command() {
    return m_command;
  }

  // 'interval()' should in the future return some more dynamic values.
  uint32_t interval() const {
    return m_interval;
  }
  void set_interval(uint32_t v) {
    m_interval = v;
  }

  torrent::utils::timer time_scheduled() const {
    return m_timeScheduled;
  }
  torrent::utils::timer next_time_scheduled() const;

  slot_void& slot() {
    return m_task.slot();
  }

private:
  std::string     m_key;
  torrent::Object m_command;

  uint32_t              m_interval;
  torrent::utils::timer m_timeScheduled;

  torrent::utils::priority_item m_task;

  // Flags for various things.
};

}

#endif
