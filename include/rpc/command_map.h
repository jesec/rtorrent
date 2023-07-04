// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_RPC_COMMAND_MAP_H
#define RTORRENT_RPC_COMMAND_MAP_H

#include <cstring>
#include <map>
#include <string>

#include <torrent/object.h>

#include "rpc/command.h"

namespace rpc {

struct command_map_comp {
  bool operator()(const char* arg1, const char* arg2) const {
    return std::strcmp(arg1, arg2) < 0;
  }
};

struct command_map_data_type {
  // Some commands will need to share data, like get/set a variable. So
  // instead of using a single virtual member function, each command
  // will register a member function pointer to be used instead.
  //
  // The any_slot should perhaps replace generic_slot?

  command_map_data_type(int flags, const char* parm, const char* doc)
    : m_flags(flags)
    , m_parm(parm)
    , m_doc(doc) {}

  command_map_data_type(const command_map_data_type& src) = default;

  command_base           m_variable;
  command_base::any_slot m_anySlot;

  int m_flags;

  const char* m_parm;
  const char* m_doc;
};

class CommandMap
  : public std::map<const char*, command_map_data_type, command_map_comp> {
public:
  using base_type =
    std::map<const char*, command_map_data_type, command_map_comp>;

  using mapped_type       = torrent::Object;
  using mapped_value_type = mapped_type::value_type;

  using base_type::const_iterator;
  using base_type::iterator;
  using base_type::key_type;
  using base_type::value_type;

  using base_type::begin;
  using base_type::end;
  using base_type::find;

  static constexpr int flag_dont_delete   = 0x1;
  static constexpr int flag_delete_key    = 0x2;
  static constexpr int flag_public        = 0x4;
  static constexpr int flag_modifiable    = 0x10;
  static constexpr int flag_is_redirect   = 0x20;
  static constexpr int flag_has_redirects = 0x40;

  static constexpr int flag_no_target      = 0x100;
  static constexpr int flag_file_target    = 0x200;
  static constexpr int flag_tracker_target = 0x400;

  CommandMap() = default;
  ~CommandMap();
  CommandMap(const CommandMap&) = delete;
  void operator=(const CommandMap&) = delete;

  bool has(const char* key) const {
    return base_type::find(key) != base_type::end();
  }
  bool has(const std::string& key) const {
    return has(key.c_str());
  }

  bool is_modifiable(const_iterator itr) {
    return itr != end() && (itr->second.m_flags & flag_modifiable);
  }

  iterator insert(key_type key, int flags, const char* parm, const char* doc);

  template<typename T, typename Slot>
  void insert_slot(key_type               key,
                   Slot                   variable,
                   command_base::any_slot targetSlot,
                   int                    flags,
                   const char*            parm,
                   const char*            doc) {
    iterator itr = insert(key, flags, parm, doc);
    itr->second.m_variable.set_function<T>(variable);
    itr->second.m_anySlot = targetSlot;
  }

  //  void                insert(key_type key, const command_map_data_type src);
  void erase(iterator itr);

  void create_redirect(key_type key_new, key_type key_dest, int flags);

  const mapped_type call(key_type key, const mapped_type& args = mapped_type());
  const mapped_type call(key_type           key,
                         target_type        target,
                         const mapped_type& args = mapped_type()) {
    return call_command(key, args, target);
  }
  const mapped_type call_catch(key_type           key,
                               target_type        target,
                               const mapped_type& args = mapped_type(),
                               const char*        err  = "Command failed: ");

  const mapped_type call_command(
    key_type           key,
    const mapped_type& arg,
    target_type        target = target_type((int)command_base::target_generic,
                                            nullptr,
                                            nullptr));
  const mapped_type call_command(
    iterator           itr,
    const mapped_type& arg,
    target_type        target = target_type((int)command_base::target_generic,
                                            nullptr,
                                            nullptr));

  const mapped_type call_command_d(key_type           key,
                                   core::Download*    download,
                                   const mapped_type& arg) {
    return call_command(
      key,
      arg,
      target_type((int)command_base::target_download, download, nullptr));
  }
  const mapped_type call_command_p(key_type           key,
                                   torrent::Peer*     peer,
                                   const mapped_type& arg) {
    return call_command(
      key, arg, target_type((int)command_base::target_peer, peer, nullptr));
  }
  const mapped_type call_command_t(key_type           key,
                                   torrent::Tracker*  tracker,
                                   const mapped_type& arg) {
    return call_command(
      key,
      arg,
      target_type((int)command_base::target_tracker, tracker, nullptr));
  }
  const mapped_type call_command_f(key_type           key,
                                   torrent::File*     file,
                                   const mapped_type& arg) {
    return call_command(
      key, arg, target_type((int)command_base::target_file, file, nullptr));
  }
};

inline target_type
make_target() {
  return { (int)command_base::target_generic, nullptr, nullptr };
}
inline target_type
make_target(int type, void* target) {
  return { type, target, nullptr };
}
inline target_type
make_target(int type, void* target1, void* target2) {
  return { type, target1, target2 };
}

template<typename T>
inline target_type
make_target(T target) {
  return { (int)target_type_id<T>::value, target, nullptr };
}

template<typename T>
inline target_type
make_target_pair(T target1, T target2) {
  return { (int)target_type_id<T, T>::value, target1, target2 };
}

// TODO: Helper-functions that really should be in the
// torrent/object.h header.

inline torrent::Object
create_object_list(const torrent::Object& o1, const torrent::Object& o2) {
  torrent::Object tmp = torrent::Object::create_list();
  tmp.as_list().push_back(o1);
  tmp.as_list().push_back(o2);
  return tmp;
}

inline torrent::Object
create_object_list(const torrent::Object& o1,
                   const torrent::Object& o2,
                   const torrent::Object& o3) {
  torrent::Object tmp = torrent::Object::create_list();
  tmp.as_list().push_back(o1);
  tmp.as_list().push_back(o2);
  tmp.as_list().push_back(o3);
  return tmp;
}

inline const CommandMap::mapped_type
CommandMap::call(key_type key, const mapped_type& args) {
  return call_command(key, args, make_target());
}

}

#endif
