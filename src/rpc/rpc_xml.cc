// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#include "buildinfo.h"

#include <functional>

#include <cctype>
#include <limits>

#include <stdlib.h>

#include "rpc/rpc_xml.h"

#include <torrent/exceptions.h>
#include <torrent/object.h>
#include <torrent/utils/string_manip.h>

#include "rpc/parse_commands.h"

#include "rpc/command.h"

#include "utils/rapidxml/rapidxml.hpp"
#include "utils/rapidxml/rapidxml_print.hpp"

using namespace rapidxml;

namespace rpc {

xml_node<>*
value_to_xml(xml_document<>& doc, const json& j) {
  xml_node<>* val_node = doc.allocate_node(node_element, "value");

  switch (j.type()) {
    case json::value_t::number_integer: {
      xml_node<>* int_node = doc.allocate_node(
        node_element,
        "int",
        doc.allocate_string(std::to_string(j.get<int>()).c_str()));
      val_node->append_node(int_node);
      break;
    }
    case json::value_t::string: {
      xml_node<>* string_node =
        doc.allocate_node(node_element,
                          "string",
                          doc.allocate_string(j.get<std::string>().c_str()));
      val_node->append_node(string_node);
      break;
    }
    case json::value_t::array: {
      xml_node<>* array_node = doc.allocate_node(node_element, "array");
      xml_node<>* data_node  = doc.allocate_node(node_element, "data");
      array_node->append_node(data_node);
      for (const auto& item : j) {
        data_node->append_node(value_to_xml(doc, item));
      }
      val_node->append_node(array_node);
      break;
    }
    case json::value_t::object: {
      xml_node<>* struct_node = doc.allocate_node(node_element, "struct");
      for (auto it = j.begin(); it != j.end(); ++it) {
        xml_node<>* member_node = doc.allocate_node(node_element, "member");
        xml_node<>* name_node   = doc.allocate_node(
          node_element, "name", doc.allocate_string(it.key().c_str()));
        member_node->append_node(name_node);
        member_node->append_node(value_to_xml(doc, it.value()));
        struct_node->append_node(member_node);
      }
      val_node->append_node(struct_node);
      break;
    }
    default:
      throw std::runtime_error("Unexpected JSON: Unexpected value type");
  }

  return val_node;
}

json
value_to_json(rapidxml::xml_node<>* node) {
  if (node == nullptr || node->first_node() == nullptr) {
    throw std::runtime_error("Invalid XML-RPC: Missing node");
  }

  auto        type_node = node->first_node();
  std::string node_name = type_node->name();

  if (node_name == "int" || node_name == "i4" || node_name == "i8") {
    try {
      return std::stoi(type_node->value());
    } catch (const std::invalid_argument&) {
      throw std::runtime_error("Invalid XML-RPC: Invalid integer value");
    }
  }

  if (node_name == "string") {
    return type_node->value();
  }

  if (node_name == "struct") {
    json obj;

    for (auto m = type_node->first_node("member"); m; m = m->next_sibling()) {
      auto nameNode  = m->first_node("name");
      auto valueNode = m->first_node("value");
      if (nameNode == nullptr || valueNode == nullptr) {
        throw std::runtime_error(
          "Invalid XML-RPC: Missing name or value in struct");
      }

      std::string name = nameNode->value();
      obj[name]        = value_to_json(valueNode);
    }

    return obj;
  }

  if (node_name == "array") {
    json array;

    auto data_node = type_node->first_node("data");
    if (data_node == nullptr) {
      throw std::runtime_error("Invalid XML-RPC: Missing data in array");
    }

    for (auto v = data_node->first_node("value"); v; v = v->next_sibling()) {
      array.push_back(value_to_json(v));
    }

    return array;
  }

  throw std::runtime_error("Invalid XML-RPC: Unexpected value type");
}

bool
send_fault(int                     faultCode,
           const std::string_view& faultString,
           IRpc::res_callback      callback) {
  auto buf_size = size_t(10) + faultString.size() + 240;
  auto buf      = new char[buf_size];

  auto count = snprintf(
    buf,
    buf_size,
    "<?xml "
    "version=\"1.0\"?><methodResponse><fault><value><struct><member><name>"
    "faultCode</name><value><int>%d</int></value></"
    "member><member><name>faultString</name><value><string>%s</string></"
    "value></member></struct></value></fault></methodResponse>",
    faultCode,
    faultString.data());

  if (count < 0) {
    delete[] buf;
    const char* response =
      "<?xml "
      "version=\"1.0\"?><methodResponse><fault><value><struct><member><name>"
      "faultCode</name><value><int>-500</int></value></"
      "member><member><name>faultString</name><value><string>null</string></"
      "value></member></struct></value></fault></methodResponse>";
    return callback(response, strlen(response));
  }

  auto result = callback(buf, count);
  delete[] buf;
  return result;
}

bool
RpcXml::process(const char* inBuffer, uint32_t length, res_callback callback) {
  auto in = std::string(inBuffer, length);

  xml_document<> in_doc;
  in_doc.parse<0>(&in[0]);

  xml_node<>* methodCallNode = in_doc.first_node("methodCall");
  if (methodCallNode == nullptr) {
    return send_fault(-501, "Invalid XML-RPC Call", callback);
  }

  xml_node<>* methodNameNode = methodCallNode->first_node("methodName");
  xml_node<>* paramsNode     = methodCallNode->first_node("params");
  if (methodCallNode == nullptr || paramsNode == nullptr) {
    return send_fault(-501, "Invalid XML-RPC Call", callback);
  }

  auto methodName = methodNameNode->value();
  json params;

  // TODO: handle base64 value type - load.raw*

  try {
    for (xml_node<>* paramNode = paramsNode->first_node("param"); paramNode;
         paramNode             = paramNode->next_sibling()) {
      params.push_back(value_to_json(paramNode->first_node("value")));
    }
  } catch (const std::runtime_error& e) {
    return send_fault(-501, e.what(), callback);
  }

  if (params.type() == json::value_t::null) {
    params = json::array();
  }

  json result;

  try {
    result = m_rpcjson->jsonrpc_call_command(methodName, params);
  } catch (const JsonRpcException& e) {
    return send_fault(-501, e.Message(), callback);
  }

  xml_document<> out_doc;
  xml_node<>*    root = out_doc.allocate_node(node_element, "methodResponse");
  out_doc.append_node(root);
  xml_node<>* out_paramsNode = out_doc.allocate_node(node_element, "params");
  xml_node<>* out_paramNode  = out_doc.allocate_node(node_element, "param");

  try {
    out_paramNode->append_node(value_to_xml(out_doc, result));
  } catch (const std::runtime_error& e) {
    return send_fault(-501, e.what(), callback);
  }

  out_paramsNode->append_node(out_paramNode);
  root->append_node(out_paramsNode);

  std::string response;
  print(std::back_inserter(response), out_doc, 0);

  return callback(response.c_str(), response.size());
}

}
