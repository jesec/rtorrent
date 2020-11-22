// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_RPC_PARSE_COMMANDS_H
#define RTORRENT_RPC_PARSE_COMMANDS_H

#include <cstring>
#include <string>

#include "command_map.h"
#include "exec_file.h"
#include "xmlrpc.h"

namespace core {
class Download;
}

namespace rpc {

// Move to another file?
extern CommandMap commands;
extern XmlRpc     xmlrpc;
extern ExecFile   execFile;

typedef std::pair<torrent::Object, const char*> parse_command_type;

// The generic parse command function, used by the rest. At some point
// the 'download' parameter should be replaced by a more generic one.
parse_command_type
parse_command(target_type target, const char* first, const char* last);
torrent::Object
parse_command_multiple(target_type target, const char* first, const char* last);

void
parse_command_execute(target_type target, torrent::Object* object);

inline torrent::Object
parse_command_single(target_type target, const char* first) {
  return parse_command(target, first, first + std::strlen(first)).first;
}
inline torrent::Object
parse_command_multiple(target_type target, const char* first) {
  return parse_command_multiple(target, first, first + std::strlen(first));
}

bool
parse_command_file(const std::string& path);
const char*
parse_command_name(const char* first, const char* last, std::string* dest);

inline torrent::Object
parse_command_single(target_type target, const std::string& cmd) {
  return parse_command(target, cmd.c_str(), cmd.c_str() + cmd.size()).first;
}

inline torrent::Object
parse_command_multiple_std(const std::string& cmd,
                           target_type        target = rpc::make_target()) {
  return parse_command_multiple(target, cmd.c_str(), cmd.c_str() + cmd.size());
}

inline void
parse_command_single_std(const std::string& cmd) {
  parse_command(make_target(), cmd.c_str(), cmd.c_str() + cmd.size());
}

inline torrent::Object
parse_command_multiple_d_nothrow(core::Download*    download,
                                 const std::string& cmd) {
  try {
    return parse_command_multiple(
      make_target(download), cmd.c_str(), cmd.c_str() + cmd.size());
  } catch (torrent::input_error& e) {
    // Log?
    return torrent::Object();
  }
}

inline torrent::Object
call_command(const char*            key,
             const torrent::Object& obj    = torrent::Object(),
             target_type            target = make_target()) {
  return commands.call_command(key, obj, target);
}
inline std::string
call_command_string(const char* key, target_type target = make_target()) {
  return commands.call_command(key, torrent::Object(), target).as_string();
}
inline int64_t
call_command_value(const char* key, target_type target = make_target()) {
  return commands.call_command(key, torrent::Object(), target).as_value();
}

inline void
call_command_set_string(const char* key, const std::string& arg) {
  commands.call_command(key, torrent::Object(arg));
}
inline void
call_command_set_std_string(const std::string& key, const std::string& arg) {
  commands.call_command(key.c_str(), torrent::Object(arg));
}
inline void
call_command_set_value(const char* key,
                       int64_t     arg,
                       target_type target = make_target()) {
  commands.call_command(key, torrent::Object(arg), target);
}

inline torrent::Object
call_command_d_range(const char*                          key,
                     core::Download*                      download,
                     torrent::Object::list_const_iterator first,
                     torrent::Object::list_const_iterator last) {
  // Change to using range ctor.
  torrent::Object             rawArgs = torrent::Object::create_list();
  torrent::Object::list_type& args    = rawArgs.as_list();

  while (first != last)
    args.push_back(*first++);

  return commands.call_command_d(key, download, rawArgs);
}

torrent::Object
call_object(const torrent::Object& command, target_type target = make_target());

inline torrent::Object
call_object_nothrow(const torrent::Object& command,
                    target_type            target = make_target()) {
  try {
    return call_object(command, target);
  } catch (torrent::input_error& e) {
    return torrent::Object();
  }
}

inline torrent::Object
call_object_d_nothrow(const torrent::Object& command,
                      core::Download*        download) {
  try {
    return call_object(command, make_target(download));
  } catch (torrent::input_error& e) {
    return torrent::Object();
  }
}

//
//
//

const torrent::Object
command_function_call_object(const torrent::Object& cmd,
                             target_type            target,
                             const torrent::Object& args);

inline const torrent::Object
command_function_call_str(const std::string&     cmd,
                          target_type            target,
                          const torrent::Object& args) {
  return command_function_call_object(torrent::Object(cmd), target, args);
}

}

#endif
