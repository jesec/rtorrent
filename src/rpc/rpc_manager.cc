// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2021, Contributors to the rTorrent project

#include <memory>

#include <torrent/exceptions.h>

#include "rpc/rpc_xml.h"

#include "rpc/rpc_manager.h"

namespace rpc {

RpcManager::RpcManager() {
  m_rpcProcessors[RPCType::XML] = new RpcXml();
}

RpcManager::~RpcManager() {
  delete static_cast<RpcXml*>(m_rpcProcessors[RPCType::XML]);
}

bool
RpcManager::dispatch(RPCType            type,
                     const char*        inBuffer,
                     uint32_t           length,
                     IRpc::res_callback callback) {
  switch (type) {
    case RPCType::XML:
      return m_rpcProcessors[RPCType::XML]->process(inBuffer, length, callback);
    default:
      throw torrent::internal_error("Invalid RPC type.");
  }
}

void
RpcManager::initialize(slot_download fun_d,
                       slot_file     fun_f,
                       slot_tracker  fun_t,
                       slot_peer     fun_p) {
  m_slotFindDownload = fun_d;
  m_slotFindFile     = fun_f;
  m_slotFindTracker  = fun_t;
  m_slotFindPeer     = fun_p;

  m_rpcProcessors[RPCType::XML]->initialize();
}

void
RpcManager::cleanup() {
  m_rpcProcessors[RPCType::XML]->cleanup();
}

bool
RpcManager::is_valid() const {
  return m_rpcProcessors[RPCType::XML]->is_valid();
}

void
RpcManager::insert_command(const char* name,
                           const char* parm,
                           const char* doc) {
  m_rpcProcessors[RPCType::XML]->insert_command(name, parm, doc);
}

}