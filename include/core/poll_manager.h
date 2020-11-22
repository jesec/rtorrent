// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_CORE_POLL_MANAGER_H
#define RTORRENT_CORE_POLL_MANAGER_H

#include "core/curl_stack.h"

namespace torrent {
class Poll;
}

namespace core {

torrent::Poll*
create_poll();

}

#endif
