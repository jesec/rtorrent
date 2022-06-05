// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_THREAD_WORKER_H
#define RTORRENT_THREAD_WORKER_H

#include <atomic>

#include "thread_base.h"
#include "protocol_thread.h"

#include <torrent/utils/cacheline.h>
#include <torrent/utils/priority_queue_default.h>

namespace rpc {
class SCgi;
}

// Check if cacheline aligned with inheritance ends up taking two
// cachelines.

class lt_cacheline_aligned ThreadWorker : public ThreadBase, public ProtocolThread{
public:
  ~ThreadWorker() override;

  const char* name() const override {
    return "rtorrent scgi";
  }

  void init_thread() override;

  void* protocol() override {
    return m_scgi;
  }
  bool set_protocol(void*) override;

  void set_rpc_log(const std::string& filename) override;

  static void start_protocol(ThreadBase* thread);
  static void msg_change_rpc_log(ThreadBase* thread);

  void queue_item(void* newFunc) override {
    ::ThreadBase::queue_item((thread_base_func)(newFunc));
  }

  torrent::Poll* poll() override {
    return ::ThreadBase::thread_base::poll();
  }

  void start_thread() override {
    ::ThreadBase::thread_base::start_thread();
  }

  bool is_active() const override {
    return ::ThreadBase::is_active();
  }
private:
  void task_touch_log();

  void change_rpc_log();

  std::atomic<rpc::SCgi*> lt_cacheline_aligned m_scgi{ nullptr };

};

#endif
