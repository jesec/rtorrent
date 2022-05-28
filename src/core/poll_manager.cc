// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#include <stdexcept>
#include <unistd.h>

#include <torrent/chunk_manager.h>
#include <torrent/exceptions.h>
#include <torrent/poll_epoll.h>
#include <torrent/poll_kqueue.h>
#include <torrent/poll_select.h>

#include "control.h"
#include "core/manager.h"
#include "core/poll_manager.h"
#include "globals.h"

namespace core {

torrent::Poll*
create_poll() {
  const char* poll_name = getenv("RTORRENT_POLL");

  // Global maximum number of opened file descriptors, for socket connections
  // (trackers, peers and RPC), files (seeding, leeching and checking) and
  // others. This is the absolute limit.
  //
  // This value can NOT change once rTorrent is loaded. However, other limits,
  // configurable by the user, would likely decide how many file descriptors
  // will actually be opened:
  //
  // - network.max_open_files=
  // - network.max_open_sockets=
  //
  // Number of files opened is further limited by the total number of files in
  // non-stopped torrents.
  //
  // Number of connections established is further limited by the condition and
  // capability of swarm, tracker connection limit, and peer connection slot
  // limit:
  //
  // - network.http.max_open=
  // - throttle.max_uploads=
  // - throttle.max_uploads.global=
  // - throttle.min_peers.normal=
  // - throttle.min_peers.seed=
  // - throttle.max_peers.normal=
  // - throttle.max_peers.seed=
  //
  // Try to decide this value from two sources, and we must use the smaller one:
  //
  // - Considering the memory constraints: divide the total physical memory
  //   available (in bytes) by 16384.
  //
  //   This yields us 65536 with 1G, and 2097152 with 32G, requiring roughly
  //   32M and 1G RAM to initialize respectively.
  //
  //   As in-effect limits are likely to be much smaller, it is acknowledged
  //   that the value could waste memory. However, it is essential to reserve
  //   the range to allow the user to increase the configurable limits, should
  //   they wish to.
  //
  // - Considering the limit imposed on the process: check the limit with
  //   sysconf(_SC_OPEN_MAX).
  //
  //   This limit is 1024 by default on most Linux systems, so in most cases,
  //   we have to use that value here (since it is smaller).
  //
  //   The limit should be increased if more connections are wanted:
  //   - kernel: /proc/sys/fs/file-max
  //   - shell: ulimit
  //   - systemd: LimitNOFILE
  int maxOpen =
    torrent::ChunkManager::estimate_max_memory_usage() / (1UL << 14);

  int maxOpenLimit = sysconf(_SC_OPEN_MAX);
  if (maxOpenLimit > 0) {
    maxOpen = std::min(maxOpen, maxOpenLimit);
  }

  torrent::Poll* poll = nullptr;

  if (poll_name != nullptr) {
    if (!strcmp(poll_name, "epoll"))
      poll = torrent::PollEPoll::create(maxOpen);
    else if (!strcmp(poll_name, "kqueue"))
      poll = torrent::PollKQueue::create(maxOpen);
    else if (!strcmp(poll_name, "select"))
      poll = torrent::PollSelect::create(maxOpen);

    if (poll == nullptr) {
      control->core()->push_log_std(std::string("Cannot enable '") + poll_name +
                                    "' based polling.");
    } else {
      control->core()->push_log_std(std::string("Using '") + poll_name +
                                    "' based polling.");
      return poll;
    }
  }

  poll = torrent::PollEPoll::create(maxOpen);
  if (poll != nullptr) {
    control->core()->push_log_std("Using 'epoll' based polling.");
    return poll;
  }

  poll = torrent::PollKQueue::create(maxOpen);
  if (poll != nullptr) {
    control->core()->push_log_std("Using 'kqueue' based polling.");
    return poll;
  }

  poll = torrent::PollSelect::create(maxOpen);
  if (poll != nullptr) {
    control->core()->push_log_std("Using 'select' based polling.");
    return poll;
  }

  throw torrent::internal_error("Could not create any Poll object.");
}

}
