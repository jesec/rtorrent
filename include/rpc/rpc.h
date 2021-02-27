// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2021, Contributors to the rTorrent project

#ifndef RTORRENT_RPC_INTERFACE_H
#define RTORRENT_RPC_INTERFACE_H

#include <cstdint>
#include <functional>

#include <torrent/exceptions.h>

namespace core {
class Download;
}

namespace torrent {
class File;
class Object;
class Tracker;
}

namespace rpc {

class IRpc {
public:
  using res_callback = std::function<bool(const char*, uint32_t)>;

  virtual void initialize() {}

  virtual void cleanup() {}

  virtual bool is_valid() const {
    return false;
  };

  virtual bool process(const char*, uint32_t, res_callback) {
    throw torrent::internal_error("RPC request not dispatched.");
  }

  virtual void insert_command(const char*, const char*, const char*) {}
};

}

#endif
