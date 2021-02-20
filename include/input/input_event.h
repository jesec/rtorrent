// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_INPUT_INPUT_EVENT_H
#define RTORRENT_INPUT_INPUT_EVENT_H

#include <functional>

#include <torrent/event.h>
#include <torrent/poll.h>

namespace input {

class InputEvent : public torrent::Event {
public:
  using slot_int = std::function<void(int)>;

  InputEvent(int fd) {
    m_fileDesc = fd;
  }

  void insert(torrent::Poll* p);
  void remove(torrent::Poll* p);

  void event_read() override;
  void event_write() override;
  void event_error() override;

  void slot_pressed(slot_int s) {
    m_slotPressed = s;
  }

private:
  slot_int m_slotPressed;
};

}

#endif
