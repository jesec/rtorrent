// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#include "config.h"

#include <torrent/exceptions.h>

#include "command_scheduler_item.h"

namespace rpc {

CommandSchedulerItem::~CommandSchedulerItem() {
  priority_queue_erase(&taskScheduler, &m_task);
}

void
CommandSchedulerItem::enable(torrent::utils::timer t) {
  if (t == torrent::utils::timer())
    throw torrent::internal_error(
      "CommandSchedulerItem::enable() t == torrent::utils::timer().");

  if (is_queued())
    disable();

  // If 'first' is zero then we execute the task
  // immediately. ''interval()'' will not return zero so we never end
  // up in an infinit loop.
  m_timeScheduled = t;
  priority_queue_insert(&taskScheduler, &m_task, t);
}

void
CommandSchedulerItem::disable() {
  m_timeScheduled = torrent::utils::timer();
  priority_queue_erase(&taskScheduler, &m_task);
}

torrent::utils::timer
CommandSchedulerItem::next_time_scheduled() const {
  if (m_interval == 0)
    return torrent::utils::timer();

  if (m_timeScheduled == torrent::utils::timer())
    throw torrent::internal_error(
      "CommandSchedulerItem::next_time_scheduled() m_timeScheduled == "
      "torrent::utils::timer().");

  torrent::utils::timer next = m_timeScheduled;

  // This should be done in a non-looping manner.
  do {
    next += torrent::utils::timer::from_seconds(m_interval);
  } while (next <= cachedTime.round_seconds());

  return next;
}

}
