// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#include "thread_base.h"

#include <cassert>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <signal.h>
#include <torrent/buildinfo.h>
#include <torrent/exceptions.h>
#include <torrent/torrent.h>
#include <torrent/utils/error_number.h>
#include <torrent/utils/log.h>
#include <unistd.h>

#include "control.h"
#include "core/manager.h"
#include "globals.h"

class lt_cacheline_aligned thread_queue_hack {
public:
  typedef ThreadBase::thread_base_func  value_type;
  typedef ThreadBase::thread_base_func* iterator;

  static const unsigned int max_size = 32;

  thread_queue_hack() {
    std::memset(this, 0, sizeof(thread_queue_hack));
  }

  void lock() {
    while (!__sync_bool_compare_and_swap(&m_lock, 0, 1))
      usleep(0);
  }
  void unlock() {
    __sync_bool_compare_and_swap(&m_lock, 1, 0);
  }

  iterator begin() {
    return m_queue;
  }
  iterator max_capacity() {
    return m_queue + max_size;
  }

  iterator end_and_lock() {
    lock();
    return std::find(begin(), max_capacity(), (value_type)NULL);
  }

  bool empty() const {
    return m_queue[0] == NULL;
  }

  void push_back(value_type v) {
    iterator itr = end_and_lock();

    if (itr == max_capacity())
      throw torrent::internal_error("Overflowed thread_queue.");

    __sync_bool_compare_and_swap(itr, NULL, v);
    unlock();
  }

  value_type* copy_and_clear(value_type* dest) {
    iterator itr = begin();
    lock();

    while (*itr != NULL)
      *dest++ = *itr++;

    clear_and_unlock();
    return dest;
  }

  void clear_and_unlock() {
    std::memset(this, 0, sizeof(thread_queue_hack));
    __sync_synchronize();
  }

private:
  int        m_lock;
  value_type m_queue[max_size + 1];
};

void
throw_shutdown_exception() {
  throw torrent::shutdown_exception();
}

ThreadBase::ThreadBase() {
  m_taskShutdown.slot() = std::bind(&throw_shutdown_exception);

  m_threadQueue = new thread_queue_hack;
}

ThreadBase::~ThreadBase() noexcept(true) {
  delete m_threadQueue;
}

// Move to libtorrent...
void
ThreadBase::stop_thread(ThreadBase* thread) {
  if (!thread->m_taskShutdown.is_queued())
    priority_queue_insert(
      &thread->m_taskScheduler, &thread->m_taskShutdown, cachedTime);
}

int64_t
ThreadBase::next_timeout_usec() {
  if (m_taskScheduler.empty())
    return torrent::utils::timer::from_seconds(600).usec();
  else if (m_taskScheduler.top()->time() <= cachedTime)
    return 0;
  else
    return (m_taskScheduler.top()->time() - cachedTime).usec();
}

void
ThreadBase::call_queued_items() {
  thread_base_func  result[thread_queue_hack::max_size];
  thread_base_func* first = result;
  thread_base_func* last =
    m_threadQueue->copy_and_clear((thread_base_func*)result);

  while (first != last && *first)
    (*first++)(this);
}

void
ThreadBase::call_events() {
  // Check for new queued items set by other threads.
  if (!m_threadQueue->empty())
    call_queued_items();

  torrent::utils::priority_queue_perform(&m_taskScheduler, cachedTime);
}

void
ThreadBase::queue_item(thread_base_func newFunc) {
  m_threadQueue->push_back(newFunc);

  // Make it also restart inactive threads?
  if (m_state == STATE_ACTIVE)
    interrupt();
}
