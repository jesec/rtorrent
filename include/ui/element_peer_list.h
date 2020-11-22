// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_UI_ELEMENT_PEER_LIST_H
#define RTORRENT_UI_ELEMENT_PEER_LIST_H

#include <torrent/peer/connection_list.h>

#include "core/download.h"
#include "ui/element_base.h"

namespace ui {

class ElementText;

class ElementPeerList : public ElementBase {
public:
  typedef std::list<torrent::Peer*> PList;

  typedef torrent::ConnectionList::signal_peer_type::iterator signal_connection;

  typedef enum { DISPLAY_LIST, DISPLAY_INFO, DISPLAY_MAX_SIZE } Display;

  ElementPeerList(core::Download* d);
  ~ElementPeerList();

  void activate(display::Frame* frame, bool focus = true);
  void disable();

  void activate_display(Display display);

private:
  inline ElementText* create_info();

  void receive_next();
  void receive_prev();

  void receive_disconnect_peer();

  void receive_peer_connected(torrent::Peer* p);
  void receive_peer_disconnected(torrent::Peer* p);

  void receive_snub_peer();
  void receive_ban_peer();

  void update_itr();

  core::Download* m_download;

  Display          m_state;
  display::Window* m_windowList;

  ElementText* m_elementInfo;

  PList           m_list;
  PList::iterator m_listItr;

  signal_connection m_peer_connected;
  signal_connection m_peer_disconnected;
};

}

#endif
