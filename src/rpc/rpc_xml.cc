// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#include "buildinfo.h"

#ifdef HAVE_XMLRPC_C

#include <functional>

#include <cctype>
#include <limits>

#include <stdlib.h>
#include <xmlrpc-c/server.h>
#ifndef XMLRPC_HAVE_I8
static_assert(false, "XMLRPC is too old");
#endif

#include "rpc/rpc_xml.h"

#include <torrent/exceptions.h>
#include <torrent/object.h>
#include <torrent/utils/string_manip.h>

#include "rpc/parse_commands.h"

#include "rpc/command.h"

namespace rpc {

class xmlrpc_error : public torrent::base_error {
public:
  xmlrpc_error(xmlrpc_env* env)
    : m_type(env->fault_code)
    , m_msg(env->fault_string) {}
  xmlrpc_error(int type, const char* msg)
    : m_type(type)
    , m_msg(msg) {}
  ~xmlrpc_error() override = default;

  virtual int type() const noexcept {
    return m_type;
  }
  const char* what() const noexcept override {
    return m_msg;
  }

private:
  int         m_type;
  const char* m_msg;
};

torrent::Object
xmlrpc_to_object(xmlrpc_env*       env,
                 xmlrpc_value*     value,
                 int               callType = 0,
                 rpc::target_type* target   = nullptr);

inline torrent::Object
xmlrpc_list_entry_to_object(xmlrpc_env* env, xmlrpc_value* src, int index) {
  xmlrpc_value* tmp;

  // reference may be incremented
  xmlrpc_array_read_item(env, src, index, &tmp);

  if (env->fault_occurred) {
    // when fault_occurred, reference is not incremented
    throw xmlrpc_error(env);
  }

  torrent::Object obj = xmlrpc_to_object(env, tmp);
  xmlrpc_DECREF(tmp);

  return obj;
}

int64_t
xmlrpc_list_entry_to_value(xmlrpc_env* env, xmlrpc_value* src, int index) {
  xmlrpc_value* tmp;

  // reference may be incremented
  xmlrpc_array_read_item(env, src, index, &tmp);

  if (env->fault_occurred) {
    // when fault_occurred, reference is not incremented
    throw xmlrpc_error(env);
  }

  switch (xmlrpc_value_type(tmp)) {
    case XMLRPC_TYPE_INT:
      int v;
      xmlrpc_read_int(env, tmp, &v);
      xmlrpc_DECREF(tmp);
      return v;

    case XMLRPC_TYPE_I8:
      xmlrpc_int64 v2;
      xmlrpc_read_i8(env, tmp, &v2);
      xmlrpc_DECREF(tmp);
      return v2;

    case XMLRPC_TYPE_STRING: {
      const char* str;

      // memory may be allocated
      xmlrpc_read_string(env, tmp, &str);

      if (env->fault_occurred) {
        // when fault_occurred, memory is not allocated
        xmlrpc_DECREF(tmp);
        throw xmlrpc_error(env);
      }

      const char* end = str;
      int64_t     v3  = ::strtoll(str, (char**)&end, 0);

      if (*str == '\0' || *end != '\0') {
        ::free((void*)str);
        xmlrpc_DECREF(tmp);
        throw xmlrpc_error(XMLRPC_TYPE_ERROR, "Invalid index.");
      }

      ::free((void*)str);
      xmlrpc_DECREF(tmp);

      return v3;
    }

    default:
      xmlrpc_DECREF(tmp);
      throw xmlrpc_error(XMLRPC_TYPE_ERROR, "Invalid type found.");
  }
}

// Consider making a helper function that creates a target_type from a
// torrent::Object, then we can just use xmlrpc_to_object.
rpc::target_type
xmlrpc_to_target(xmlrpc_env* env, xmlrpc_value* value) {
  rpc::target_type target;

  switch (xmlrpc_value_type(value)) {
    case XMLRPC_TYPE_STRING: {
      const char* str;

      // memory may be allocated
      xmlrpc_read_string(env, value, &str);

      if (env->fault_occurred) {
        // when fault_occurred, memory is not allocated
        throw xmlrpc_error(env);
      }

      if (std::strlen(str) == 0) {
        // When specifying void, we require a zero-length string.
        ::free((void*)str);
        return rpc::make_target();

      } else if (std::strlen(str) < 40) {
        ::free((void*)str);
        throw xmlrpc_error(XMLRPC_TYPE_ERROR, "Unsupported target type found.");
      }

      core::Download* download = rpc.slot_find_download()(str);

      if (download == nullptr) {
        ::free((void*)str);
        throw xmlrpc_error(XMLRPC_TYPE_ERROR, "Could not find info-hash.");
      }

      if (std::strlen(str) == 40) {
        ::free((void*)str);
        return rpc::make_target(download);
      }

      if (std::strlen(str) < 42 || str[40] != ':') {
        ::free((void*)str);
        throw xmlrpc_error(XMLRPC_TYPE_ERROR, "Unsupported target type found.");
      }

      // Files:    "<hash>:f<index>"
      // Trackers: "<hash>:t<index>"

      int         index;
      const char* end_ptr = str + 42;

      switch (str[41]) {
        case 'f':
          index = ::strtol(str + 42, (char**)&end_ptr, 0);

          if (*str == '\0' || *end_ptr != '\0') {
            ::free((void*)str);
            throw xmlrpc_error(XMLRPC_TYPE_ERROR, "Invalid index.");
          }

          target = rpc::make_target(command_base::target_file,
                                    rpc.slot_find_file()(download, index));
          break;

        case 't':
          index = ::strtol(str + 42, (char**)&end_ptr, 0);

          if (*str == '\0' || *end_ptr != '\0') {
            ::free((void*)str);
            throw xmlrpc_error(XMLRPC_TYPE_ERROR, "Invalid index.");
          }

          target = rpc::make_target(command_base::target_tracker,
                                    rpc.slot_find_tracker()(download, index));
          break;

        case 'p': {
          torrent::HashString hash;
          const char*         hash_end =
            torrent::hash_string_from_hex_c_str(str + 42, hash);

          if (hash_end == end_ptr || *hash_end != '\0') {
            ::free((void*)str);
            throw xmlrpc_error(XMLRPC_TYPE_ERROR, "Not a hash string.");
          }

          target = rpc::make_target(command_base::target_peer,
                                    rpc.slot_find_peer()(download, hash));
          break;
        }
        default:
          ::free((void*)str);
          throw xmlrpc_error(XMLRPC_TYPE_ERROR,
                             "Unsupported target type found.");
      }

      ::free((void*)str);

      // Check if the target pointer is NULL.
      if (target.second == nullptr)
        throw xmlrpc_error(XMLRPC_TYPE_ERROR, "Invalid index.");

      return target;
    }

    default:
      return rpc::make_target();
  }
}

rpc::target_type
xmlrpc_to_index_type(int index, int callType, core::Download* download) {
  void* result;

  switch (callType) {
    case command_base::target_file:
      result = rpc.slot_find_file()(download, index);
      break;
    case command_base::target_tracker:
      result = rpc.slot_find_tracker()(download, index);
      break;
    default:
      result = nullptr;
      break;
  }

  if (result == nullptr)
    throw xmlrpc_error(XMLRPC_TYPE_ERROR, "Invalid index.");

  return rpc::make_target(callType, result);
}

torrent::Object
xmlrpc_to_object(xmlrpc_env*       env,
                 xmlrpc_value*     value,
                 int               callType,
                 rpc::target_type* target) {
  switch (xmlrpc_value_type(value)) {
    case XMLRPC_TYPE_INT:
      int v;
      xmlrpc_read_int(env, value, &v);

      return torrent::Object((int64_t)v);

    case XMLRPC_TYPE_I8:
      xmlrpc_int64 v2;
      xmlrpc_read_i8(env, value, &v2);

      return torrent::Object((int64_t)v2);

      //     case XMLRPC_TYPE_BOOL:
      //     case XMLRPC_TYPE_DOUBLE:
      //     case XMLRPC_TYPE_DATETIME:

    case XMLRPC_TYPE_STRING:

      if (callType != command_base::target_generic) {
        // When the call type is not supposed to be void, we'll try to
        // convert it to a command target. It's not that important that
        // it is converted to the right type here, as an mismatch will
        // be caught when executing the command.
        *target = xmlrpc_to_target(env, value);
        return torrent::Object();

      } else {
        const char* valueString;

        // memory may be allocated
        xmlrpc_read_string(env, value, &valueString);

        if (env->fault_occurred) {
          // when fault_occurred, memory is not allocated
          throw xmlrpc_error(env);
        }

        torrent::Object result = torrent::Object(std::string(valueString));

        // Urgh, seriously?
        // yes, std::string() above already copied it
        ::free((void*)valueString);

        return result;
      }

    case XMLRPC_TYPE_BASE64: {
      size_t      valueSize;
      const char* valueString;

      // memory may be allocated
      xmlrpc_read_base64(
        env, value, &valueSize, (const unsigned char**)&valueString);

      if (env->fault_occurred) {
        // when fault_occurred, memory is not allocated
        throw xmlrpc_error(env);
      }

      torrent::Object result =
        torrent::Object(std::string(valueString, valueSize));

      ::free((void*)valueString);

      return result;
    }

    case XMLRPC_TYPE_ARRAY: {
      unsigned int current = 0;
      unsigned int last    = xmlrpc_array_size(env, value);

      if (env->fault_occurred)
        throw xmlrpc_error(env);

      if (callType != command_base::target_generic && last != 0) {
        if (last < 1)
          throw xmlrpc_error(XMLRPC_TYPE_ERROR, "Too few arguments.");

        xmlrpc_value* tmp;

        // reference may be incremented
        xmlrpc_array_read_item(env, value, current++, &tmp);

        if (env->fault_occurred) {
          // when fault_occurred, reference is not incremented
          throw xmlrpc_error(env);
        }

        *target = xmlrpc_to_target(env, tmp);
        xmlrpc_DECREF(tmp);

        if (env->fault_occurred)
          throw xmlrpc_error(env);

        if (target->first == command_base::target_download &&
            (callType == command_base::target_file ||
             callType == command_base::target_tracker)) {
          // If we have a download target and the call type requires
          // another contained type, then we try to use the next
          // parameter as the index to support old-style calls.

          if (current == last)
            throw xmlrpc_error(XMLRPC_TYPE_ERROR,
                               "Too few arguments, missing index.");

          *target = xmlrpc_to_index_type(
            xmlrpc_list_entry_to_value(env, value, current++),
            callType,
            (core::Download*)target->second);
        }
      }

      if (current + 1 < last) {
        torrent::Object             result  = torrent::Object::create_list();
        torrent::Object::list_type& listRef = result.as_list();

        while (current != last)
          listRef.push_back(xmlrpc_list_entry_to_object(env, value, current++));

        return result;

      } else if (current + 1 == last) {
        return xmlrpc_list_entry_to_object(env, value, current);

      } else {
        return torrent::Object();
      }
    }

    //     case XMLRPC_TYPE_STRUCT:
    //     case XMLRPC_TYPE_C_PTR:
    //     case XMLRPC_TYPE_NIL:
    //     case XMLRPC_TYPE_DEAD:
    default:
      throw xmlrpc_error(XMLRPC_TYPE_ERROR, "Unsupported type found.");
  }
}

xmlrpc_value*
object_to_xmlrpc(xmlrpc_env* env, const torrent::Object& object) {
  switch (object.type()) {
    case torrent::Object::TYPE_VALUE:
      return xmlrpc_i8_new(env, object.as_value());

    case torrent::Object::TYPE_STRING: {
      // The versions that support I8 do implicit utf-8 validation.
      xmlrpc_value* result = xmlrpc_string_new(env, object.as_string().c_str());

      if (env->fault_occurred) {
        xmlrpc_env_clean(env);
        xmlrpc_env_init(env);

        const std::string& str = object.as_string();
        char* buffer = static_cast<char*>(calloc(str.size() + 1, sizeof(char)));
        char* dst    = buffer;
        for (std::string::const_iterator itr = str.begin(); itr != str.end();
             ++itr)
          *dst++ =
            ((*itr < 0x20 && *itr != '\r' && *itr != '\n' && *itr != '\t') ||
             (*itr & 0x80))
              ? '?'
              : *itr;
        *dst = 0;

        result = xmlrpc_string_new(env, buffer);
        free(buffer);
      }

      return result;
    }

    case torrent::Object::TYPE_LIST: {
      xmlrpc_value* result = xmlrpc_array_new(env);

      for (torrent::Object::list_const_iterator itr  = object.as_list().begin(),
                                                last = object.as_list().end();
           itr != last;
           itr++) {
        xmlrpc_value* item = object_to_xmlrpc(env, *itr);
        xmlrpc_array_append_item(env, result, item);
        xmlrpc_DECREF(item);
      }

      return result;
    }

    case torrent::Object::TYPE_MAP: {
      xmlrpc_value* result = xmlrpc_struct_new(env);

      for (torrent::Object::map_const_iterator itr  = object.as_map().begin(),
                                               last = object.as_map().end();
           itr != last;
           itr++) {
        xmlrpc_value* item = object_to_xmlrpc(env, itr->second);
        xmlrpc_struct_set_value(env, result, itr->first.c_str(), item);
        xmlrpc_DECREF(item);
      }

      return result;
    }

    case torrent::Object::TYPE_DICT_KEY: {
      xmlrpc_value* result = xmlrpc_array_new(env);

      xmlrpc_value* key_item = object_to_xmlrpc(env, object.as_dict_key());
      xmlrpc_array_append_item(env, result, key_item);
      xmlrpc_DECREF(key_item);

      if (object.as_dict_obj().is_list()) {
        for (torrent::Object::list_const_iterator
               itr  = object.as_dict_obj().as_list().begin(),
               last = object.as_dict_obj().as_list().end();
             itr != last;
             itr++) {
          xmlrpc_value* item = object_to_xmlrpc(env, *itr);
          xmlrpc_array_append_item(env, result, item);
          xmlrpc_DECREF(item);
        }
      } else {
        xmlrpc_value* arg_item = object_to_xmlrpc(env, object.as_dict_obj());
        xmlrpc_array_append_item(env, result, arg_item);
        xmlrpc_DECREF(arg_item);
      }

      return result;
    }

    default:
      return xmlrpc_int_new(env, 0);
  }
}

xmlrpc_value*
xmlrpc_call_command(xmlrpc_env* env, xmlrpc_value* args, void* voidServerInfo) {
  CommandMap::iterator itr = commands.find((const char*)voidServerInfo);

  if (itr == commands.end()) {
    xmlrpc_env_set_fault(env,
                         XMLRPC_PARSE_ERROR,
                         ("Command \"" +
                          std::string((const char*)voidServerInfo) +
                          "\" does not exist.")
                           .c_str());
    return nullptr;
  }

  try {
    torrent::Object  object;
    rpc::target_type target = rpc::make_target();

    if (itr->second.m_flags & CommandMap::flag_no_target)
      xmlrpc_to_object(env, args, command_base::target_generic, &target)
        .swap(object);
    else if (itr->second.m_flags & CommandMap::flag_file_target)
      xmlrpc_to_object(env, args, command_base::target_file, &target)
        .swap(object);
    else if (itr->second.m_flags & CommandMap::flag_tracker_target)
      xmlrpc_to_object(env, args, command_base::target_tracker, &target)
        .swap(object);
    else
      xmlrpc_to_object(env, args, command_base::target_any, &target)
        .swap(object);

    if (env->fault_occurred)
      return nullptr;

    return object_to_xmlrpc(env,
                            rpc::commands.call_command(itr, object, target));

  } catch (xmlrpc_error& e) {
    xmlrpc_env_set_fault(env, e.type(), e.what());
    return nullptr;

  } catch (torrent::local_error& e) {
    xmlrpc_env_set_fault(env, XMLRPC_PARSE_ERROR, e.what());
    return nullptr;
  }
}

void
RpcXml::initialize() {
  m_env = new xmlrpc_env;

  xmlrpc_env_init((xmlrpc_env*)m_env);
  m_registry = xmlrpc_registry_new((xmlrpc_env*)m_env);

  xmlrpc_limit_set(XMLRPC_XML_SIZE_LIMIT_ID,
                   std::numeric_limits<size_t>::max());
  xmlrpc_registry_set_dialect(
    (xmlrpc_env*)m_env, (xmlrpc_registry*)m_registry, xmlrpc_dialect_i8);
}

void
RpcXml::cleanup() {
  if (!is_valid())
    return;

  xmlrpc_registry_free((xmlrpc_registry*)m_registry);
  xmlrpc_env_clean((xmlrpc_env*)m_env);

  delete (xmlrpc_env*)m_env;
}

bool
RpcXml::process(const char* inBuffer, uint32_t length, res_callback callback) {
  xmlrpc_env localEnv;
  xmlrpc_env_init(&localEnv);

  xmlrpc_mem_block* memblock = xmlrpc_registry_process_call(
    &localEnv, (xmlrpc_registry*)m_registry, nullptr, inBuffer, length);

  if (localEnv.fault_occurred && localEnv.fault_code == XMLRPC_INTERNAL_ERROR)
    throw torrent::internal_error("Internal error in XMLRPC.");

  bool result = callback((const char*)xmlrpc_mem_block_contents(memblock),
                         xmlrpc_mem_block_size(memblock));

  xmlrpc_mem_block_free(memblock);
  xmlrpc_env_clean(&localEnv);
  return result;
}

void
RpcXml::insert_command(const char* name, const char* parm, const char* doc) {
  xmlrpc_env localEnv;
  xmlrpc_env_init(&localEnv);

  xmlrpc_registry_add_method_w_doc(&localEnv,
                                   (xmlrpc_registry*)m_registry,
                                   nullptr,
                                   name,
                                   &xmlrpc_call_command,
                                   const_cast<char*>(name),
                                   parm,
                                   doc);

  if (localEnv.fault_occurred)
    throw torrent::internal_error("Fault occured while inserting xmlrpc call.");

  xmlrpc_env_clean(&localEnv);
}

}

#endif
