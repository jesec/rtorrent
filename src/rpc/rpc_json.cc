// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2021, Contributors to the rTorrent project

#include "rpc/rpc_json.h"

#ifdef HAVE_JSON

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <iterator>
#include <string>
#include <string_view>
#include <vector>

#include <nlohmann/json.hpp>

#include <torrent/common.h>
#include <torrent/hash_string.h>
#include <torrent/torrent.h>

#include "rpc/command.h"
#include "rpc/command_map.h"
#include "rpc/parse_commands.h"
#include "thread_base.h"
#include "utils/jsonrpc/common.h"

using jsonrpccxx::JsonRpcException;
using nlohmann::json;

namespace rpc {

void
string_to_target(const std::string_view& targetString,
                 bool                    requireIndex,
                 rpc::target_type*       target) {
  // target_any: ''
  // target_download: <hash>
  // target_file: <hash>:f<index>
  // target_peer: <hash>:p<index>
  // target_tracker: <hash>:t<index>

  if (targetString.size() == 0 && !requireIndex) {
    return;
  }

  // Length of SHA1 hash is 40
  if (targetString.size() < 40) {
    throw torrent::input_error("invalid parameters: invalid target");
  }

  std::string_view hash;
  char             type = 'd';
  std::string_view index;

  const auto& delimPos = targetString.find_first_of(':', 40);
  if (delimPos == std::string_view::npos ||
      delimPos + 2 >= targetString.size()) {
    if (requireIndex) {
      throw torrent::input_error("invalid parameters: no index");
    }
    hash = targetString;
  } else {
    hash  = targetString.substr(0, delimPos);
    type  = targetString[delimPos + 1];
    index = targetString.substr(delimPos + 2);
  }

  // many internal functions expect C-style NULL-terminated strings

  core::Download* download =
    rpc.slot_find_download()(std::string(hash).c_str());

  if (download == nullptr) {
    throw torrent::input_error("invalid parameters: info-hash not found");
  }

  try {
    switch (type) {
      case 'd':
        *target = rpc::make_target(download);
        break;
      case 'f':
        *target = rpc::make_target(
          command_base::target_file,
          rpc.slot_find_file()(download, std::stoi(std::string(index))));
        break;
      case 't':
        *target = rpc::make_target(
          command_base::target_tracker,
          rpc.slot_find_tracker()(download, std::stoi(std::string(index))));
        break;
      case 'p':
        *target = rpc::make_target(
          command_base::target_peer,
          rpc.slot_find_peer()(download, std::string(index).c_str()));
        break;
      default:
        throw torrent::input_error(
          "invalid parameters: unexpected target type");
    }
  } catch (const std::logic_error&) {
    throw torrent::input_error("invalid parameters: invalid index");
  }

  if (target == nullptr || target->second == nullptr) {
    throw torrent::input_error(
      "invalid parameters: unable to find requested target");
  }
}

torrent::Object
json_to_object(const json& value, int callType, rpc::target_type* target) {
  switch (value.type()) {
    case json::value_t::number_integer:
      return torrent::Object(value.get<int64_t>());
    case json::value_t::boolean:
      return value.get<bool>() ? torrent::Object(int64_t(1))
                               : torrent::Object(int64_t(0));
    case json::value_t::string:
      return torrent::Object(value.get<std::string>());
    case json::value_t::array: {
      const auto& count = value.size();

      uint8_t start = 0;

      if (callType != command_base::target_generic) {
        if (count < 1) {
          throw torrent::input_error("invalid parameters: too few");
        }

        if (!value[0].is_string()) {
          throw torrent::input_error(
            "invalid parameters: target must be a string");
        }

        string_to_target(value[0].get<std::string_view>(),
                         callType != command_base::target_any,
                         target);

        // start from the second member since the first is the target
        ++start;
      }

      if (count == 0) {
        return torrent::Object();
      } else if (start == count - 1) {
        return json_to_object(value[start], callType, target);
      } else {
        torrent::Object             result  = torrent::Object::create_list();
        torrent::Object::list_type& listRef = result.as_list();

        auto current = start;
        while (current != count) {
          listRef.push_back(json_to_object(value[current], callType, target));
          ++current;
        }

        return result;
      }
    }
    default:
      throw torrent::input_error("invalid parameters: unexpected data type");
  }
}

json
object_to_json(const torrent::Object& object) noexcept {
  switch (object.type()) {
    case torrent::Object::TYPE_VALUE:
      return object.as_value();
    case torrent::Object::TYPE_STRING:
      return object.as_string();
    case torrent::Object::TYPE_LIST: {
      json result = json::array();
      std::transform(
        object.as_list().cbegin(),
        object.as_list().cend(),
        std::back_inserter(result),
        [](const torrent::Object& element) { return object_to_json(element); });
      return result;
    }
    case torrent::Object::TYPE_MAP: {
      json result = json::object();
      std::for_each(
        object.as_map().cbegin(),
        object.as_map().cend(),
        [&result](
          const torrent::Object::map_type::const_iterator::value_type& pair) {
          result.emplace(pair.first, object_to_json(pair.second));
        });
      return result;
    }
    case torrent::Object::TYPE_DICT_KEY: {
      json result = json::array();

      result.push_back(object_to_json(object.as_dict_key()));

      const auto& dict_obj = object.as_dict_obj();
      if (dict_obj.is_list()) {
        std::transform(dict_obj.as_list().cbegin(),
                       dict_obj.as_list().cend(),
                       std::back_inserter(result),
                       [](const torrent::Object& element) {
                         return object_to_json(element);
                       });
      } else {
        result.push_back(object_to_json(dict_obj));
      }

      return result;
    }
    default:
      return 0;
  }
}

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

  if (std::string_view("system.listMethods") == method) {
    json methods = json::array();
    std::transform(
      commands.cbegin(),
      commands.cend(),
      std::back_inserter(methods),
      [](const std::pair<const char* const, rpc::command_map_data_type>&
           mapping) { return mapping.first; });
    return methods;
  }

  CommandMap::iterator itr = commands.find(method.c_str());

  if (itr == commands.end()) {
    throw JsonRpcException(-32601, "method not found: " + method);
  }

  try {
    torrent::Object  object;
    rpc::target_type target = rpc::make_target();

    torrent::thread_base::acquire_global_lock();
    torrent::main_thread()->interrupt();

    if (itr->second.m_flags & CommandMap::flag_no_target) {
      json_to_object(params, command_base::target_generic, &target)
        .swap(object);
    } else if (itr->second.m_flags & CommandMap::flag_file_target) {
      json_to_object(params, command_base::target_file, &target).swap(object);
    } else if (itr->second.m_flags & CommandMap::flag_tracker_target) {
      json_to_object(params, command_base::target_tracker, &target)
        .swap(object);
    } else {
      json_to_object(params, command_base::target_any, &target).swap(object);
    }

    const auto& result = rpc::commands.call_command(itr, object, target);

    torrent::thread_base::release_global_lock();
    return object_to_json(result);
  } catch (torrent::input_error& e) {
    torrent::thread_base::release_global_lock();
    throw JsonRpcException(-32602, e.what());
  } catch (torrent::local_error& e) {
    torrent::thread_base::release_global_lock();
    throw JsonRpcException(-32000, e.what());
  }
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