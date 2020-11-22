// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#include <stdexcept>
#include <torrent/exceptions.h>
#include <torrent/poll_epoll.h>
#include <torrent/poll_kqueue.h>
#include <torrent/poll_select.h>
#include <unistd.h>

#include "control.h"
#include "core/manager.h"
#include "core/poll_manager.h"
#include "globals.h"

namespace core {

torrent::Poll*
create_poll() {
  const char* poll_name = getenv("RTORRENT_POLL");

  int maxOpen = sysconf(_SC_OPEN_MAX);

  torrent::Poll* poll = NULL;

  if (poll_name != NULL) {
    if (!strcmp(poll_name, "epoll"))
      poll = torrent::PollEPoll::create(maxOpen);
    else if (!strcmp(poll_name, "kqueue"))
      poll = torrent::PollKQueue::create(maxOpen);
    else if (!strcmp(poll_name, "select"))
      poll = torrent::PollSelect::create(maxOpen);

    if (poll == NULL)
      control->core()->push_log_std(std::string("Cannot enable '") + poll_name +
                                    "' based polling.");
  }

  if (poll != NULL)
    control->core()->push_log_std(std::string("Using '") + poll_name +
                                  "' based polling.");

  else if ((poll = torrent::PollEPoll::create(maxOpen)) != NULL)
    control->core()->push_log_std("Using 'epoll' based polling.");

  else if ((poll = torrent::PollKQueue::create(maxOpen)) != NULL)
    control->core()->push_log_std("Using 'kqueue' based polling.");

  else if ((poll = torrent::PollSelect::create(maxOpen)) != NULL)
    control->core()->push_log_std("Using 'select' based polling.");

  else
    throw torrent::internal_error("Could not create any Poll object.");

  return poll;
}

}
