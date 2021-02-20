// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_DISPLAY_PEER_LIST_H
#define RTORRENT_DISPLAY_PEER_LIST_H

#include <list>
#include <torrent/peer/peer.h>

#include "display/window.h"

namespace core {
class Download;
}

namespace display {

class WindowPeerList : public Window {
public:
  using PList = std::list<torrent::Peer*>;

  WindowPeerList(core::Download* d, PList* l, PList::iterator* f);

  void redraw() override;

private:
  int done_percentage(torrent::Peer* p);

  core::Download* m_download;

  PList*           m_list;
  PList::iterator* m_focus;
};

}

#endif
