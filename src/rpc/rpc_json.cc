// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2021, Contributors to the rTorrent project

#include <string_view>

#include "rpc/rpc_json.h"

#ifdef HAVE_JSON

#include <nlohmann/json.hpp>

#include "rpc/command_map.h"
#include "rpc/parse_commands.h"

using jsonrpccxx::JsonRpcException;
using nlohmann::json;

namespace rpc {

json
jsonrpc_call_command(const std::string& method, const json& params) {
  if (params.type() != json::value_t::array) {
    if (params.type() == json::value_t::object) {
      throw JsonRpcException(
        -32602, "invalid parameter: procedure doesn't support named parameter");
    } else {
      throw JsonRpcException(
        -32600, "invalid request: params field must be an array, object");
    }
  }

  CommandMap::iterator itr = commands.find(method.c_str());

  if (itr == commands.end()) {
    throw JsonRpcException(-32601, "method not found: " + method);
  }

  throw JsonRpcException(-32600, "not implemented");
}

void
RpcJson::initialize() {
  m_jsonrpc = new jsonrpccxx::JsonRpc2Server(&jsonrpc_call_command);
}

void
RpcJson::cleanup() {
  delete m_jsonrpc;
}

bool
RpcJson::is_valid() const {
  return m_jsonrpc != nullptr;
}

bool
RpcJson::process(const char* inBuffer, uint32_t length, res_callback callback) {
  const std::string& response =
    m_jsonrpc->HandleRequest(std::string_view(inBuffer, length));

  return callback(response.c_str(), response.size());
}

}

#endif