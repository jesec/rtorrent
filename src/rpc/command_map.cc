// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#include "config.h"

#include <torrent/data/file_list_iterator.h>
#include <torrent/exceptions.h>
#include <torrent/object.h>
#include <vector>

// Get better logging...
#include "control.h"
#include "core/manager.h"
#include "globals.h"

#include "command.h"
#include "command_map.h"

// For XMLRPC stuff, clean up.
#include "parse_commands.h"
#include "xmlrpc.h"

namespace rpc {

command_base::stack_type command_base::current_stack;

CommandMap::~CommandMap() {
  std::vector<const char*> keys;

  for (iterator itr = base_type::begin(), last = base_type::end(); itr != last;
       itr++) {
    //     if (!(itr->second.m_flags & flag_dont_delete))
    //       delete itr->second.m_variable;

    if (itr->second.m_flags & flag_delete_key)
      keys.push_back(itr->first);
  }

  for (std::vector<const char*>::iterator itr = keys.begin(), last = keys.end();
       itr != last;
       itr++)
    delete[] * itr;
}

CommandMap::iterator
CommandMap::insert(key_type key, int flags, const char* parm, const char* doc) {
  iterator itr = base_type::find(key);

  if (itr != base_type::end())
    throw torrent::internal_error(
      "CommandMap::insert(...) tried to insert an already existing key.");

  // TODO: This is not honoring the public_xmlrpc flags!!!
  if (rpc::xmlrpc.is_valid() && (flags & flag_public_xmlrpc))
    // if (rpc::xmlrpc.is_valid())
    rpc::xmlrpc.insert_command(key, parm, doc);

  return base_type::insert(
    itr, value_type(key, command_map_data_type(flags, parm, doc)));
}

// void
// CommandMap::insert(key_type key, const command_map_data_type src) {
//   iterator itr = base_type::find(key);

//   if (itr != base_type::end())
//     throw torrent::internal_error("CommandMap::insert(...) tried to insert an
//     already existing key.");

//   itr = base_type::insert(itr, value_type(key,
//   command_map_data_type(src.m_variable, src.m_flags | flag_dont_delete,
//   src.m_parm, src.m_doc)));

//   // We can assume all the slots are the same size.
//   itr->second.m_anySlot = src.m_anySlot;
// }

void
CommandMap::erase(iterator itr) {
  if (itr == end())
    return;

  // TODO: Remove the redirects instead...
  if (itr->second.m_flags & flag_has_redirects)
    throw torrent::input_error("Can't erase a command that has redirects.");

  //   if (!(itr->second.m_flags & flag_dont_delete))
  //     delete itr->second.m_variable;

  const char* key = itr->second.m_flags & flag_delete_key ? itr->first : NULL;

  base_type::erase(itr);
  delete[] key;
}

void
CommandMap::create_redirect(key_type key_new, key_type key_dest, int flags) {
  iterator new_itr  = base_type::find(key_new);
  iterator dest_itr = base_type::find(key_dest);

  if (dest_itr == base_type::end())
    throw torrent::input_error(
      "Tried to redirect to a key that doesn't exist: '" +
      std::string(key_dest) + "'.");

  if (new_itr != base_type::end())
    throw torrent::input_error(
      "Tried to create a redirect key that already exists: '" +
      std::string(key_new) + "'.");

  if (dest_itr->second.m_flags & flag_is_redirect)
    throw torrent::input_error(
      "Tried to redirect to a key that is not marked 'flag_is_redirect': '" +
      std::string(key_dest) + "'.");

  dest_itr->second.m_flags |= flag_has_redirects;

  flags |= dest_itr->second.m_flags &
           ~(flag_delete_key | flag_has_redirects | flag_public_xmlrpc);

  // TODO: This is not honoring the public_xmlrpc flags!!!
  if (rpc::xmlrpc.is_valid() && (flags & flag_public_xmlrpc))
    rpc::xmlrpc.insert_command(
      key_new, dest_itr->second.m_parm, dest_itr->second.m_doc);

  iterator itr = base_type::insert(
    base_type::end(),
    value_type(key_new,
               command_map_data_type(
                 flags, dest_itr->second.m_parm, dest_itr->second.m_doc)));

  // We can assume all the slots are the same size.
  itr->second.m_variable = dest_itr->second.m_variable;
  itr->second.m_anySlot  = dest_itr->second.m_anySlot;
}

const CommandMap::mapped_type
CommandMap::call_catch(key_type           key,
                       target_type        target,
                       const mapped_type& args,
                       const char*        err) {
  try {
    return call_command(key, args, target);
  } catch (torrent::input_error& e) {
    control->core()->push_log((err + std::string(e.what())).c_str());
    return torrent::Object();
  }
}

const CommandMap::mapped_type
CommandMap::call_command(key_type           key,
                         const mapped_type& arg,
                         target_type        target) {
  iterator itr = base_type::find(key);

  if (itr == base_type::end())
    throw torrent::input_error("Command \"" + std::string(key) +
                               "\" does not exist.");

  return itr->second.m_anySlot(&itr->second.m_variable, target, arg);
}

const CommandMap::mapped_type
CommandMap::call_command(iterator           itr,
                         const mapped_type& arg,
                         target_type        target) {
  return itr->second.m_anySlot(&itr->second.m_variable, target, arg);
}

}
