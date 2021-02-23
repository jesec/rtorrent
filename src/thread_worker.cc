// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#include <cassert>
#include <fcntl.h>
#include <unistd.h>

#include <torrent/exceptions.h>
#include <torrent/utils/path.h>

#include "control.h"
#include "globals.h"
#include "thread_worker.h"

#include "core/manager.h"
#include "rpc/parse_commands.h"
#include "rpc/scgi.h"
#include "rpc/xmlrpc.h"

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
ThreadWorker::set_scgi(rpc::SCgi* scgi) {
  if (m_scgi != nullptr) {
    return false;
  }

  m_scgi = scgi;

  change_xmlrpc_log();

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

  if (thread->scgi() == nullptr)
    throw torrent::internal_error(
      "Tried to start SCGI but object was not present.");

  thread->scgi()->activate();
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
