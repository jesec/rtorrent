// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2021, Contributors to the rTorrent project

#ifndef RTORRENT_RPC_INTERFACE_H
#define RTORRENT_RPC_INTERFACE_H

#include <cstdint>
#include <functional>

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

  virtual void initialize() = 0;

  virtual void cleanup() = 0;

  virtual bool is_valid() const = 0;

  virtual bool process(const char*  inBuffer,
                       uint32_t     length,
                       res_callback callback) = 0;

  virtual void insert_command(const char* name,
                              const char* parm,
                              const char* doc) = 0;
};

}

#endif
