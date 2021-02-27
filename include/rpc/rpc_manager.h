// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2021, Contributors to the rTorrent project

#ifndef RTORRENT_RPC_MANAGER_H
#define RTORRENT_RPC_MANAGER_H

#include <array>
#include <cstdint>
#include <functional>
#include <memory>

#include "rpc/command.h"
#include "rpc/rpc.h"

namespace rpc {
class RpcManager {
public:
  using slot_download = std::function<core::Download*(const char*)>;
  using slot_file = std::function<torrent::File*(core::Download*, uint32_t)>;
  using slot_tracker =
    std::function<torrent::Tracker*(core::Download*, uint32_t)>;
  using slot_peer =
    std::function<torrent::Peer*(core::Download*, const torrent::HashString&)>;

  enum RPCType { XML, JSON, RPC_TYPE_SIZE };

  RpcManager();
  ~RpcManager();

  bool dispatch(RPCType            type,
                const char*        inBuffer,
                uint32_t           length,
                IRpc::res_callback callback);

  void initialize(slot_download fun_d,
                  slot_file     fun_f,
                  slot_tracker  fun_t,
                  slot_peer     fun_p);

  bool is_initialized() const;

  void cleanup();

  void insert_command(const char* name, const char* parm, const char* doc);

  const slot_download& slot_find_download() const {
    return m_slotFindDownload;
  }
  const slot_file& slot_find_file() const {
    return m_slotFindFile;
  }
  const slot_tracker& slot_find_tracker() const {
    return m_slotFindTracker;
  }
  const slot_peer& slot_find_peer() const {
    return m_slotFindPeer;
  }

private:
  std::array<IRpc*, RPC_TYPE_SIZE> m_rpcProcessors{ nullptr };

  bool m_initialized;

  slot_download m_slotFindDownload;
  slot_file     m_slotFindFile;
  slot_tracker  m_slotFindTracker;
  slot_peer     m_slotFindPeer;
};
}

#endif
