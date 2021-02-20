// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#include "thread_worker.h"
#include "control.h"
#include "globals.h"

#include <cassert>
#include <fcntl.h>
#include <torrent/exceptions.h>
#include <torrent/utils/path.h>
#include <unistd.h>

#include "core/manager.h"
#include "rpc/parse_commands.h"
#include "rpc/scgi.h"
#include "rpc/xmlrpc.h"

ThreadWorker::~ThreadWorker() {
  if (m_safe.scgi) {
    delete m_safe.scgi;
  }
}

void
ThreadWorker::init_thread() {
  m_poll  = core::create_poll();
  m_state = STATE_INITIALIZED;
}

bool
ThreadWorker::set_scgi(rpc::SCgi* scgi) {
  if (!__sync_bool_compare_and_swap(&m_safe.scgi, nullptr, scgi))
    return false;

  change_xmlrpc_log();

  // The xmlrpc process call requires a global lock.
  //   m_safe.scgi->set_slot_process(utils::mem_fn(&rpc::xmlrpc,
  //   &rpc::XmlRpc::process));

  // Synchronize in order to ensure the worker thread sees the updated
  // SCgi object.
  __sync_synchronize();
  queue_item((thread_base_func)&start_scgi);
  return true;
}

void
ThreadWorker::set_xmlrpc_log(const std::string& filename) {
  m_xmlrpcLog = filename;

  queue_item((thread_base_func)&msg_change_xmlrpc_log);
}

void
ThreadWorker::start_scgi(ThreadBase* baseThread) {
  ThreadWorker* thread = (ThreadWorker*)baseThread;

  if (thread->m_safe.scgi == nullptr)
    throw torrent::internal_error(
      "Tried to start SCGI but object was not present.");

  thread->m_safe.scgi->activate();
}

void
ThreadWorker::msg_change_xmlrpc_log(ThreadBase* baseThread) {
  ThreadWorker* thread = (ThreadWorker*)baseThread;

  acquire_global_lock();
  thread->change_xmlrpc_log();
  release_global_lock();
}

void
ThreadWorker::change_xmlrpc_log() {
  if (scgi() == nullptr)
    return;

  if (scgi()->log_fd() != -1) {
    ::close(scgi()->log_fd());
    scgi()->set_log_fd(-1);
    control->core()->push_log("Closed XMLRPC log.");
  }

  if (m_xmlrpcLog.empty())
    return;

  scgi()->set_log_fd(open(torrent::utils::path_expand(m_xmlrpcLog).c_str(),
                          O_WRONLY | O_APPEND | O_CREAT,
                          0644));

  if (scgi()->log_fd() == -1) {
    control->core()->push_log_std("Could not open XMLRPC log file '" +
                                  m_xmlrpcLog + "'.");
    return;
  }

  control->core()->push_log_std("Logging XMLRPC events to '" + m_xmlrpcLog +
                                "'.");
}
