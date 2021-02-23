// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#include <stdexcept>
#include <unistd.h>

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

  int maxOpen = sysconf(_SC_OPEN_MAX);

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
