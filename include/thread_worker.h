// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_THREAD_WORKER_H
#define RTORRENT_THREAD_WORKER_H

#include "thread_base.h"

#include <torrent/utils/cacheline.h>
#include <torrent/utils/priority_queue_default.h>

namespace rpc {
class SCgi;
}

// Check if cacheline aligned with inheritance ends up taking two
// cachelines.

class lt_cacheline_aligned ThreadWorker : public ThreadBase {
public:
  ~ThreadWorker() override;

  const char* name() const override {
    return "rtorrent scgi";
  }

  void init_thread() override;

  rpc::SCgi* scgi() {
    return m_safe.scgi;
  }
  bool set_scgi(rpc::SCgi* scgi);

  void set_xmlrpc_log(const std::string& filename);

  static void start_scgi(ThreadBase* thread);
  static void msg_change_xmlrpc_log(ThreadBase* thread);

private:
  void task_touch_log();

  void change_xmlrpc_log();

  struct lt_cacheline_aligned safe_type {
    rpc::SCgi* scgi{ nullptr };
  };

  safe_type m_safe;

  // The following types shall only be modified while holding the
  // global lock.
  std::string m_xmlrpcLog;
};

#endif
