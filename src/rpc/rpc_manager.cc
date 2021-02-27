// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2021, Contributors to the rTorrent project

#include <cstring>
#include <memory>

#include <torrent/exceptions.h>

#include "rpc/rpc_json.h"
#include "rpc/rpc_xml.h"

#include "rpc/rpc_manager.h"

namespace rpc {

RpcManager::RpcManager() {
  m_rpcProcessors[RPCType::XML]  = new RpcXml();
  m_rpcProcessors[RPCType::JSON] = new RpcJson();
}

RpcManager::~RpcManager() {
  delete static_cast<RpcXml*>(m_rpcProcessors[RPCType::XML]);
  delete static_cast<RpcJson*>(m_rpcProcessors[RPCType::JSON]);
}

bool
RpcManager::dispatch(RPCType            type,
                     const char*        inBuffer,
                     uint32_t           length,
                     IRpc::res_callback callback) {
  switch (type) {
    case RPCType::XML: {
      if (m_rpcProcessors[RPCType::XML]->is_valid()) {
        return m_rpcProcessors[RPCType::XML]->process(
          inBuffer, length, callback);
      } else {
        const char* response =
          "<?xml version=\"1.0\"?><methodResponse><fault><value><string>XMLRPC "
          "not supported</string></value></fault></methodResponse>";
        return callback(response, strlen(response));
      }
    }
    case RPCType::JSON: {
      if (m_rpcProcessors[RPCType::JSON]->is_valid()) {
        return m_rpcProcessors[RPCType::JSON]->process(
          inBuffer, length, callback);
      } else {
        const char* response =
          "{\"jsonrpc\":\"2.0\",\"error\":{\"code\":-32601,\"message\":\"JSON-"
          "RPC not supported\"},\"id\":\"1\"}";
        return callback(response, strlen(response));
      }
    }
    default:
      throw torrent::internal_error("Invalid RPC type.");
  }
}

void
RpcManager::initialize(slot_download fun_d,
                       slot_file     fun_f,
                       slot_tracker  fun_t,
                       slot_peer     fun_p) {
  m_initialized = true;

  m_slotFindDownload = fun_d;
  m_slotFindFile     = fun_f;
  m_slotFindTracker  = fun_t;
  m_slotFindPeer     = fun_p;

  m_rpcProcessors[RPCType::XML]->initialize();
  m_rpcProcessors[RPCType::JSON]->initialize();
}

void
RpcManager::cleanup() {
  m_rpcProcessors[RPCType::XML]->cleanup();
  m_rpcProcessors[RPCType::JSON]->cleanup();
}

bool
RpcManager::is_initialized() const {
  return m_initialized;
}

void
RpcManager::insert_command(const char* name,
                           const char* parm,
                           const char* doc) {
  m_rpcProcessors[RPCType::XML]->insert_command(name, parm, doc);
  m_rpcProcessors[RPCType::JSON]->insert_command(name, parm, doc);
}

}