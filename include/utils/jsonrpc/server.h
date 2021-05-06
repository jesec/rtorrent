// SPDX-License-Identifier: MIT
// Copyright (C) 2019, Peter Spiess-Knafl <dev@spiessknafl.at>
// https://github.com/jsonrpcx/json-rpc-cxx, commit fa878e6829

// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2021, Contributors to the rTorrent project
// Imported and modified for the rTorrent project

#ifndef RTORRENT_UTILS_JSONRPC_SERVER_H
#define RTORRENT_UTILS_JSONRPC_SERVER_H

#include <string>

#include "common.h"

namespace jsonrpccxx {
class JsonRpcServer {
public:
  using JsonRpcHandler =
    std::function<json(const std::string& name, const json& params)>;

  JsonRpcServer(JsonRpcHandler handler)
    : m_handler(handler) {}
  virtual ~JsonRpcServer()                                           = default;
  virtual std::string HandleRequest(const std::string_view& request) = 0;

protected:
  JsonRpcHandler m_handler;
};

class JsonRpc2Server : public JsonRpcServer {
public:
  JsonRpc2Server(JsonRpcHandler handler)
    : JsonRpcServer(handler) {}
  ~JsonRpc2Server() override = default;

  std::string HandleRequest(const std::string_view& requestString) override {
    try {
      json request = json::parse(requestString);
      if (request.is_array()) {
        json result = json::array();
        for (json& r : request) {
          json res = this->HandleSingleRequest(r);
          if (!res.is_null()) {
            result.push_back(std::move(res));
          }
        }
        return result.dump(-1, ' ', false, json::error_handler_t::replace);
      } else if (request.is_object()) {
        json res = HandleSingleRequest(request);
        if (!res.is_null()) {
          return res.dump(-1, ' ', false, json::error_handler_t::replace);
        } else {
          return "";
        }
      } else {
        return json{
          { "id", nullptr },
          { "error",
            { { "code", -32600 },
              { "message", "invalid request: expected array or object" } } },
          { "jsonrpc", "2.0" }
        }.dump();
      }
    } catch (json::parse_error& e) {
      return json{
        { "id", nullptr },
        { "error",
          { { "code", -32700 },
            { "message", std::string("parse error: ") + e.what() } } },
        { "jsonrpc", "2.0" }
      }.dump();
    } catch (json::exception& e) {
      return json{
        { "id", nullptr },
        { "error",
          { { "code", -32700 },
            { "message", std::string("compose error: ") + e.what() } } },
        { "jsonrpc", "2.0" }
      }.dump();
    }
  }

private:
  json HandleSingleRequest(json& request) {
    json id = nullptr;
    if (valid_id(request)) {
      id = request["id"];
    }
    try {
      return ProcessSingleRequest(request);
    } catch (JsonRpcException& e) {
      json error = { { "code", e.Code() }, { "message", e.Message() } };
      if (!e.Data().is_null()) {
        error["data"] = e.Data();
      }
      return json{ { "id", id }, { "error", error }, { "jsonrpc", "2.0" } };
    } catch (std::exception& e) {
      return json{
        { "id", id },
        { "error",
          { { "code", -32603 },
            { "message",
              std::string("internal server error: ") + e.what() } } },
        { "jsonrpc", "2.0" }
      };
    } catch (...) {
      return json{ { "id", id },
                   { "error",
                     { { "code", -32603 },
                       { "message", std::string("internal server error") } } },
                   { "jsonrpc", "2.0" } };
    }
  }

  json ProcessSingleRequest(json& request) {
    if (!has_key_type(request, "jsonrpc", json::value_t::string) ||
        request["jsonrpc"] != "2.0") {
      throw JsonRpcException(
        -32600, R"(invalid request: missing jsonrpc field set to "2.0")");
    }
    if (!has_key_type(request, "method", json::value_t::string)) {
      throw JsonRpcException(-32600,
                             "invalid request: method field must be a string");
    }
    if (!valid_id(request)) {
      throw JsonRpcException(
        -32600, "invalid request: id field must be a number, string or null");
    }
    if (has_key(request, "params") &&
        !(request["params"].is_array() || request["params"].is_object() ||
          request["params"].is_null())) {
      throw JsonRpcException(
        -32600,
        "invalid request: params field must be an array, object or null");
    }
    if (!has_key(request, "params") ||
        has_key_type(request, "params", json::value_t::null)) {
      request["params"] = json::array();
    }

    const auto& result = m_handler(request["method"], request["params"]);

    return { { "jsonrpc", "2.0" },
             { "id", request["id"] },
             { "result", result } };
  }
};
}

#endif
