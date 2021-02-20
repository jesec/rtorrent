// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_UTILS_THREAD_BASE_H
#define RTORRENT_UTILS_THREAD_BASE_H

#include <pthread.h>
#include <sys/types.h>

#include <torrent/utils/priority_queue_default.h>
#include <torrent/utils/thread_base.h>

#include "core/poll_manager.h"

// Move this class to libtorrent.

class thread_queue_hack;

class ThreadBase : public torrent::thread_base {
public:
  using priority_queue   = torrent::utils::priority_queue_default;
  using thread_base_func = void (*)(ThreadBase*);

  ThreadBase();
  ~ThreadBase() override;

  priority_queue& task_scheduler() {
    return m_taskScheduler;
  }

  // Throw torrent::shutdown_exception to stop the thread.
  static void stop_thread(ThreadBase* thread);

  // ATM, only interaction with a thread's allowed by other threads is
  // through the queue_item call.

  void queue_item(thread_base_func newFunc);

protected:
  int64_t next_timeout_usec() override;

  void call_queued_items();
  void call_events() override;

  // TODO: Add thread name.

  // The timer needs to be sync'ed when updated...

  torrent::utils::priority_queue_default m_taskScheduler;

  torrent::utils::priority_item m_taskShutdown;

  // Temporary hack to pass messages to a thread. This really needs to
  // be cleaned up and/or integrated into the priority queue itself.
  thread_queue_hack* m_threadQueue;
};

#endif
