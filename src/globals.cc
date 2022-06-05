// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#include "globals.h"

torrent::utils::priority_queue_default taskScheduler;
torrent::utils::timer                  cachedTime;

Control*      control       = nullptr;
ProtocolThread* worker_thread = nullptr;
