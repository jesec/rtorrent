// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2021, Contributors to the rTorrent project

#ifndef RTORRENT_RPC_RPC_JSON_H
#define RTORRENT_RPC_RPC_JSON_H

#include "buildinfo.h"

#include <functional>

#ifdef HAVE_JSON
#include "utils/jsonrpc/common.h"
#include "utils/jsonrpc/server.h"
#include <nlohmann/json.hpp>

using jsonrpccxx::JsonRpcException;
using nlohmann::json;
#endif

#include "rpc/rpc.h"

namespace rpc {

class RpcJson final : public IRpc {
#ifdef HAVE_JSON
public:
  void initialize() override;

  void cleanup() override;

  bool is_valid() const override;

  bool process(const char*  inBuffer,
               uint32_t     length,
               res_callback callback) override;

  void insert_command(const char*, const char*, const char*) override {}

  json jsonrpc_call_command(const std::string& method, const json& params);

private:
  jsonrpccxx::JsonRpc2Server* m_jsonrpc;
#endif
};

}

#endif
