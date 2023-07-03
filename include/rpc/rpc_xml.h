// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_RPC_RPC_XML_H
#define RTORRENT_RPC_RPC_XML_H

#include "buildinfo.h"

#include <functional>

#include "rpc/rpc.h"
#include "rpc/rpc_json.h"

namespace rpc {

class RpcXml final : public IRpc {
public:
  RpcXml(RpcJson* rpcjson)
    : m_rpcjson(rpcjson) {}

  void initialize() {}

  void cleanup() {}

  bool is_valid() const override {
    return m_rpcjson != nullptr && m_rpcjson->is_valid();
  }

  bool process(const char*  inBuffer,
               uint32_t     length,
               res_callback callback) override;

  void insert_command(const char* name, const char* parm, const char* doc) {}

private:
  RpcJson* m_rpcjson;
};

}

#endif
