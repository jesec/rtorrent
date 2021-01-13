// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef TORRENT_GLOBALS_H
#define TORRENT_GLOBALS_H

#include <torrent/utils/priority_queue_default.h>
#include <torrent/utils/timer.h>

#include "thread_base.h"
#include "thread_worker.h"

class Control;

// The cachedTime timer should only be updated by the main thread to
// avoid potential problems in timing calculations. Code really should
// be reviewed and fixed in order to avoid any potential problems, and
// then made updates properly sync'ed with memory barriers.

extern torrent::utils::priority_queue_default taskScheduler;
extern torrent::utils::timer                  cachedTime;

extern Control*      control;
extern ThreadWorker* worker_thread;

#endif
