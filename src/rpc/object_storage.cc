// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#include "rpc/parse.h"
#include "rpc/parse_commands.h"

#include "rpc/object_storage.h"

namespace rpc {

const unsigned int object_storage::flag_generic_type;
const unsigned int object_storage::flag_bool_type;
const unsigned int object_storage::flag_value_type;
const unsigned int object_storage::flag_string_type;
const unsigned int object_storage::flag_list_type;
const unsigned int object_storage::flag_function_type;
const unsigned int object_storage::flag_multi_type;

const unsigned int object_storage::mask_type;

const unsigned int object_storage::flag_constant;
const unsigned int object_storage::flag_static;
const unsigned int object_storage::flag_private;
const unsigned int object_storage::flag_rlookup;

const size_t object_storage::key_size;

object_storage::local_iterator
object_storage::find_local(const torrent::raw_string& key) {
  std::size_t n =
    hash_fixed_key_type::hash(key.data(), key.size()) % bucket_count();

  for (local_iterator itr = begin(n), last = end(n); itr != last; itr++)
    if (itr->first.size() == key.size() &&
        std::memcmp(itr->first.data(), key.data(), key.size()) == 0)
      return itr;

  return end(bucket_count());
}

object_storage::local_iterator
object_storage::find_local_const(const torrent::raw_string& key,
                                 unsigned int               type) {
  local_iterator itr = find_local(key);

  if (itr == end(bucket_count()))
    throw torrent::input_error("Key not found.");

  if ((type != 0 && (itr->second.flags & mask_type) != type))
    throw torrent::input_error("Object is wrong type or const.");

  return itr;
}

object_storage::local_iterator
object_storage::find_local_mutable(const torrent::raw_string& key,
                                   unsigned int               type) {
  local_iterator itr = find_local(key);

  if (itr == end(bucket_count()))
    throw torrent::input_error("Key not found.");

  if ((type != 0 && (itr->second.flags & mask_type) != type) ||
      itr->second.flags & flag_constant)
    throw torrent::input_error("Object is wrong type or const.");

  return itr;
}

object_storage::iterator
object_storage::insert(const char*            key_data,
                       uint32_t               key_size,
                       const torrent::Object& rawObject,
                       unsigned int           flags) {
  if (std::find(key_data, key_data + key_size, '\0') != key_data + key_size)
    throw torrent::input_error("Found nul-char in string.");

  // Check for size > key_size.
  // Check for empty string.

  bool            use_raw = false;
  torrent::Object object;

  switch (flags & mask_type) {
    case flag_bool_type:
      object = !!convert_to_value(rawObject);
      break;
    case flag_value_type:
      object = convert_to_value(rawObject);
      break;
    case flag_string_type:
      object = convert_to_string(rawObject);
      break;
    case flag_list_type:
      use_raw = true;
      break;
    case flag_function_type:
      use_raw = true;
      break;
    case flag_multi_type:
      object = torrent::Object::create_map();
      break;
  }

  if (!(flags & mask_type))
    throw torrent::input_error(
      "No type flags set when calling object_storage::insert.");

  if ((flags & flag_rlookup) &&
      (!(flags & flag_static) || !(flags & flag_multi_type)))
    throw torrent::input_error("Cannot insert non-static or non-multi-type "
                               "object with rlookup enabled.");

  std::pair<iterator, bool> result = base_type::insert(
    std::make_pair(key_type(key_data, key_size), object_storage_node()));

  if (!result.second)
    throw torrent::input_error("Key already exists in object_storage.");

  result.first->second.flags  = flags;
  result.first->second.object = use_raw ? rawObject : object;

  return result.first;
}

bool
object_storage::has_flag(const torrent::raw_string& key, unsigned int flag) {
  local_iterator itr = find_local_const(key);
  return itr->second.flags & flag;
}

void
object_storage::enable_flag(const torrent::raw_string& key, unsigned int flag) {
  local_iterator itr = find_local_mutable(key);
  itr->second.flags |= (flag & (flag_constant));
}

const torrent::Object&
object_storage::get(const torrent::raw_string& key) {
  local_iterator itr = find_local_const(key);
  return itr->second.object;
}

const torrent::Object&
object_storage::set_bool(const torrent::raw_string& key, int64_t object) {
  local_iterator itr        = find_local_mutable(key, flag_bool_type);
  return itr->second.object = !!object;
}

const torrent::Object&
object_storage::set_value(const torrent::raw_string& key, int64_t object) {
  local_iterator itr        = find_local_mutable(key, flag_value_type);
  return itr->second.object = object;
}

const torrent::Object&
object_storage::set_string(const torrent::raw_string& key,
                           const std::string&         object) {
  local_iterator itr        = find_local_mutable(key, flag_string_type);
  return itr->second.object = object;
}

const torrent::Object&
object_storage::set_list(const torrent::raw_string&        key,
                         const torrent::Object::list_type& object) {
  local_iterator itr = find_local_mutable(key, flag_list_type);
  return itr->second.object =
           torrent::Object::create_list_range(object.begin(), object.end());
}

void
object_storage::list_push_back(const torrent::raw_string& key,
                               const torrent::Object&     object) {
  local_iterator itr = find_local_mutable(key, flag_list_type);
  itr->second.object.as_list().push_back(object);
}

const torrent::Object&
object_storage::set_function(const torrent::raw_string& key,
                             const std::string&         object) {
  local_iterator itr        = find_local_mutable(key, flag_function_type);
  return itr->second.object = object;
}

torrent::Object
object_storage::call_function(const torrent::raw_string& key,
                              target_type                target,
                              const torrent::Object&     object) {
  local_iterator itr = find_local_const(key);

  switch (itr->second.flags & mask_type) {
    case flag_function_type:
    case flag_multi_type:
      return command_function_call_object(itr->second.object, target, object);
    default:
      throw torrent::input_error("Key not found or wrong type.");
  }
}

bool
object_storage::has_multi_key(const torrent::raw_string& key,
                              const std::string&         cmd_key) {
  local_iterator itr = find_local_const(key, flag_multi_type);
  return itr->second.object.has_key(cmd_key);
}

void
object_storage::erase_multi_key(const torrent::raw_string& key,
                                const std::string&         cmd_key) {
  local_iterator itr = find_local_mutable(key, flag_multi_type);

  itr->second.object.erase_key(cmd_key);

  if (!(itr->second.flags & flag_rlookup))
    return;

  // Remove the rlookup entry.
  rlookup_iterator r_itr = m_rlookup.find(cmd_key);

  if (r_itr == m_rlookup.end())
    return;

  rlookup_mapped_iterator rm_itr =
    std::find_if(r_itr->second.begin(),
                 r_itr->second.end(),
                 [key](value_type* v) { return key == v->first; });

  if (rm_itr != r_itr->second.end())
    r_itr->second.erase(rm_itr);
}

void
object_storage::set_multi_key_obj(const torrent::raw_string& key,
                                  const std::string&         cmd_key,
                                  const torrent::Object&     object) {
  if (!object.is_string() && !object.is_dict_key() && !object.is_list())
    throw torrent::input_error("Object is wrong type.");

  local_iterator itr = find_local_mutable(key, flag_multi_type);

  if (itr->second.flags & flag_rlookup) {
    rlookup_iterator r_itr = m_rlookup.find(cmd_key);

    if (r_itr == m_rlookup.end())
      r_itr =
        m_rlookup.insert(std::make_pair(cmd_key, rlookup_type::mapped_type()))
          .first;

    if (std::find_if(
          r_itr->second.begin(), r_itr->second.end(), [key](value_type* v) {
            return key == v->first;
          }) == r_itr->second.end())
      r_itr->second.push_back(&*itr);
  }

  itr->second.object.insert_key(cmd_key, object);
}

torrent::Object::list_type
object_storage::rlookup_list(const std::string& cmd_key) {
  torrent::Object::list_type result;

  rlookup_iterator r_itr = m_rlookup.find(cmd_key);

  if (r_itr != m_rlookup.end())
    std::transform(r_itr->second.begin(),
                   r_itr->second.end(),
                   std::back_inserter(result),
                   [](value_type* v) { return v->first.c_str(); });

  return result;
}

void
object_storage::rlookup_clear(const std::string& cmd_key) {
  rlookup_iterator r_itr = m_rlookup.find(cmd_key);

  if (r_itr == m_rlookup.end())
    return;

  for (rlookup_mapped_iterator first = r_itr->second.begin(),
                               last  = r_itr->second.end();
       first != last;
       first++)
    (*first)->second.object.erase_key(cmd_key);

  r_itr->second.clear();
}

}
