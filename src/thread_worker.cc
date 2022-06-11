// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#include <fcntl.h>
#include <unistd.h>

#include <torrent/exceptions.h>
#include <torrent/utils/path.h>

#include "control.h"
#include "globals.h"
#include "thread_worker.h"

#include "core/manager.h"
#include "rpc/scgi.h"

ThreadWorker::~ThreadWorker() {
  if (m_scgi) {
    delete m_scgi;
  }
}

void
ThreadWorker::init_thread() {
  m_poll  = core::create_poll();
  m_state = STATE_INITIALIZED;
}

bool
ThreadWorker::set_protocol(void* scgi) {
  if (m_scgi != nullptr) {
    return false;
  }

  m_scgi = static_cast<rpc::SCgi*>(scgi);

  change_rpc_log();

  ::ThreadBase::queue_item((thread_base_func)start_protocol);
  return true;
}

void
ThreadWorker::set_rpc_log(const std::string& filename) {
  m_rpcLog = filename;

  ::ThreadBase::queue_item((thread_base_func)msg_change_rpc_log);
}

void
ThreadWorker::start_protocol(ThreadBase* baseThread) {
  ThreadWorker* thread = (ThreadWorker*)baseThread;

  if (thread->protocol() == nullptr)
    throw torrent::internal_error(
      "Tried to start SCGI but object was not present.");

  ((rpc::SCgi*)(thread->protocol()))->activate();
}

void
ThreadWorker::msg_change_rpc_log(ThreadBase* baseThread) {
  ThreadWorker* thread = (ThreadWorker*)baseThread;

  acquire_global_lock();
  thread->change_rpc_log();
  release_global_lock();
}

void
ThreadWorker::change_rpc_log() {
  auto work_protocol = static_cast<rpc::SCgi*>(protocol());
  if (work_protocol == nullptr)
    return;

  if (work_protocol->log_fd() != -1) {
    ::close(work_protocol->log_fd());
    work_protocol->set_log_fd(-1);
    control->core()->push_log("Closed RPC log.");
  }

  if (m_rpcLog.empty())
    return;

  work_protocol->set_log_fd(open(torrent::utils::path_expand(m_rpcLog).c_str(),
                                 O_WRONLY | O_APPEND | O_CREAT,
                                 0644));

  if (work_protocol->log_fd() == -1) {
    control->core()->push_log_std("Could not open RPC log file '" + m_rpcLog +
                                  "'.");
    return;
  }

  control->core()->push_log_std("Logging RPC events to '" + m_rpcLog + "'.");
}