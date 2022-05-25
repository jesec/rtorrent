// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#include <cstdio>
#include <functional>
#include <regex>

#include <torrent/connection_manager.h>
#include <torrent/data/download_data.h>
#include <torrent/data/file.h>
#include <torrent/data/file_list.h>
#include <torrent/download/resource_manager.h>
#include <torrent/peer/connection_list.h>
#include <torrent/peer/peer_list.h>
#include <torrent/rate.h>
#include <torrent/throttle.h>
#include <torrent/tracker.h>
#include <torrent/tracker_controller.h>
#include <torrent/tracker_list.h>
#include <torrent/utils/error_number.h>
#include <torrent/utils/file_stat.h>
#include <torrent/utils/log.h>
#include <torrent/utils/option_strings.h>
#include <torrent/utils/path.h>
#include <torrent/utils/socket_address.h>
#include <torrent/utils/string_manip.h>
#include <unistd.h>

#include "core/download.h"
#include "core/download_store.h"
#include "core/manager.h"
#include "rpc/parse.h"

#include "command_helpers.h"
#include "control.h"
#include "globals.h"

std::string
retrieve_d_base_path(core::Download* download) {
  if (download->file_list()->is_multi_file())
    return download->file_list()->frozen_root_dir();
  else
    return download->file_list()->empty()
             ? std::string()
             : download->file_list()->at(0)->frozen_path();
}

std::string
retrieve_d_base_filename(core::Download* download) {
  const std::string* base;

  if (download->file_list()->is_multi_file())
    base = &download->file_list()->frozen_root_dir();
  else
    base = &download->file_list()->at(0)->frozen_path();

  std::string::size_type split = base->rfind('/');

  if (split == std::string::npos)
    return *base;
  else
    return base->substr(split + 1);
}

torrent::Object
apply_d_change_link(core::Download*                   download,
                    const torrent::Object::list_type& args,
                    int                               changeType) {
  if (args.size() != 3)
    throw torrent::input_error("Wrong argument count.");

  torrent::Object::list_const_iterator itr = args.begin();

  const std::string& type    = (itr++)->as_string();
  const std::string& prefix  = (itr++)->as_string();
  const std::string& postfix = (itr++)->as_string();

  if (type.empty())
    throw torrent::input_error("Invalid arguments.");

  std::string target;
  std::string link;

  if (type == "base_path") {
    target =
      rpc::call_command_string("d.base_path", rpc::make_target(download));
    link = torrent::utils::path_expand(
      prefix +
      rpc::call_command_string("d.base_path", rpc::make_target(download)) +
      postfix);

  } else if (type == "base_filename") {
    target =
      rpc::call_command_string("d.base_path", rpc::make_target(download));
    link = torrent::utils::path_expand(
      prefix +
      rpc::call_command_string("d.base_filename", rpc::make_target(download)) +
      postfix);

    //   } else if (type == "directory_path") {
    //     target = rpc::call_command_string("d.directory",
    //     rpc::make_target(download)); link =
    //     torrent::utils::path_expand(prefix +
    //     rpc::call_command_string("d.base_path", rpc::make_target(download)) +
    //     postfix);

  } else if (type == "tied") {
    link = torrent::utils::path_expand(
      rpc::call_command_string("d.tied_to_file", rpc::make_target(download)));

    if (link.empty())
      return torrent::Object();

    link = torrent::utils::path_expand(prefix + link + postfix);
    target =
      rpc::call_command_string("d.base_path", rpc::make_target(download));

  } else {
    throw torrent::input_error("Unknown type argument.");
  }

  switch (changeType) {
    case 0:
      if (symlink(target.c_str(), link.c_str()) == -1) {
        lt_log_print(torrent::LOG_TORRENT_WARN,
                     "create_link failed: %s",
                     torrent::utils::error_number::current().message().c_str());
      }
      break;

    case 1: {
      torrent::utils::file_stat fileStat;
      torrent::utils::error_number::clear_global();

      if (!fileStat.update_link(link) || !fileStat.is_link() ||
          unlink(link.c_str()) == -1) {
        lt_log_print(torrent::LOG_TORRENT_WARN,
                     "delete_link failed: %s",
                     torrent::utils::error_number::current().message().c_str());
      }
      break;
    }
    default:
      break;
  }

  return torrent::Object();
}

torrent::Object
apply_d_delete_tied(core::Download* download) {
  const std::string& tie =
    rpc::call_command_string("d.tied_to_file", rpc::make_target(download));

  if (tie.empty())
    return torrent::Object();

  if (::unlink(torrent::utils::path_expand(tie).c_str()) == -1)
    control->core()->push_log_std(
      "Could not unlink tied file: " +
      torrent::utils::error_number::current().message());

  rpc::call_command(
    "d.tied_to_file.set", std::string(), rpc::make_target(download));
  return torrent::Object();
}

void
apply_d_directory(core::Download* download, const std::string& name) {
  if (!download->file_list()->is_multi_file())
    download->set_root_directory(name);
  else if (name.empty() || *name.rbegin() == '/')
    download->set_root_directory(name + download->info()->name());
  else
    download->set_root_directory(name + "/" + download->info()->name());
}

torrent::Object
apply_d_connection_type(core::Download* download, const std::string& name) {
  torrent::Download::ConnectionType t =
    (torrent::Download::ConnectionType)torrent::option_find_string(
      torrent::OPTION_CONNECTION_TYPE, name.c_str());

  download->download()->set_connection_type(t);
  return torrent::Object();
}

torrent::Object
apply_d_choke_heuristics(core::Download*    download,
                         const std::string& name,
                         bool               is_down) {
  torrent::Download::HeuristicType t =
    (torrent::Download::HeuristicType)torrent::option_find_string(
      torrent::OPTION_CHOKE_HEURISTICS, name.c_str());

  if (is_down)
    download->download()->set_download_choke_heuristic(t);
  else
    download->download()->set_upload_choke_heuristic(t);

  return torrent::Object();
}

const char*
retrieve_d_priority_str(core::Download* download) {
  switch (download->priority()) {
    case 0:
      return "off";
    case 1:
      return "low";
    case 2:
      return "normal";
    case 3:
      return "high";
    default:
      throw torrent::input_error("Priority out of range.");
  }
}

torrent::Object
retrieve_d_ratio(core::Download* download) {
  if (download->is_hash_checking())
    return int64_t();

  int64_t bytesDone = download->download()->bytes_done();
  int64_t upTotal   = download->info()->up_rate()->total();

  return bytesDone > 0 ? (1000 * upTotal) / bytesDone : 0;
}

torrent::Object
apply_d_custom(core::Download*                   download,
               const torrent::Object::list_type& args) {
  torrent::Object::list_const_iterator itr = args.begin();

  if (itr == args.end())
    throw torrent::bencode_error("Missing key argument.");

  const std::string& key = itr->as_string();

  if (++itr == args.end())
    throw torrent::bencode_error("Missing value argument.");

  download->bencode()
    ->get_key("rtorrent")
    .insert_preserve_copy("custom", torrent::Object::create_map())
    .first->second.insert_key(key, itr->as_string());
  return torrent::Object();
}

torrent::Object
retrieve_d_custom(core::Download* download, const std::string& key) {
  try {
    return download->bencode()
      ->get_key("rtorrent")
      .get_key("custom")
      .get_key_string(key);

  } catch (torrent::bencode_error& e) {
    return std::string();
  }
}

torrent::Object
retrieve_d_custom_throw(core::Download* download, const std::string& key) {
  try {
    return download->bencode()
      ->get_key("rtorrent")
      .get_key("custom")
      .get_key_string(key);

  } catch (torrent::bencode_error& e) {
    throw torrent::input_error("No such custom value.");
  }
}

torrent::Object
retrieve_d_custom_if_z(core::Download*                   download,
                       const torrent::Object::list_type& args) {
  torrent::Object::list_const_iterator itr = args.begin();
  if (itr == args.end())
    throw torrent::bencode_error("d.custom.if_z: Missing key argument.");
  const std::string& key = (itr++)->as_string();
  if (key.empty())
    throw torrent::bencode_error("d.custom.if_z: Empty key argument.");
  if (itr == args.end())
    throw torrent::bencode_error("d.custom.if_z: Missing default argument.");

  try {
    const std::string& val = download->bencode()
                               ->get_key("rtorrent")
                               .get_key("custom")
                               .get_key_string(key);
    return val.empty() ? itr->as_string() : val;
  } catch (torrent::bencode_error& e) {
    return itr->as_string();
  }
}

torrent::Object
retrieve_d_custom_map(core::Download*                   download,
                      bool                              keys_only,
                      const torrent::Object::list_type& args) {
  if (args.begin() != args.end())
    throw torrent::bencode_error("d.custom.keys/items takes no arguments.");

  torrent::Object result =
    keys_only ? torrent::Object::create_list() : torrent::Object::create_map();
  torrent::Object::map_type& entries =
    download->bencode()->get_key("rtorrent").get_key("custom").as_map();

  for (torrent::Object::map_type::const_iterator itr  = entries.begin(),
                                                 last = entries.end();
       itr != last;
       itr++) {
    if (keys_only)
      result.as_list().push_back(itr->first);
    else
      result.as_map()[itr->first] = itr->second;
  }

  return result;
}

torrent::Object
retrieve_d_bitfield(core::Download* download) {
  const torrent::Bitfield* bitField =
    download->download()->file_list()->bitfield();

  if (bitField->empty())
    return torrent::Object("");

  return torrent::Object(
    torrent::utils::transform_hex(bitField->begin(), bitField->end()));
}

struct call_add_d_peer_t {
  call_add_d_peer_t(core::Download* d, int port)
    : m_download(d)
    , m_port(port) {}

  void operator()(const sockaddr* sa, int) {
    if (sa == nullptr) {
      lt_log_print(torrent::LOG_TORRENT_WARN,
                   "could not resolve hostname for added peer");
    } else {
      m_download->download()->add_peer(sa, m_port);
    }
  }

  core::Download* m_download;
  int             m_port;
};

void
apply_d_add_peer(core::Download* download, const std::string& arg) {
  int  port, ret;
  char dummy;
  char host[1024];

  if (download->download()->info()->is_private())
    throw torrent::input_error("Download is private.");

  ret = std::sscanf(arg.c_str(), "[%64[^]]]:%i%c", host, &port, &dummy);

  if (ret < 1)
    ret = std::sscanf(arg.c_str(), "%1023[^:]:%i%c", host, &port, &dummy);

  if (ret == 1)
    port = 6881;
  else if (ret != 2)
    throw torrent::input_error("Could not parse host.");

  if (port < 1 || port > 65535)
    throw torrent::input_error("Invalid port number.");

  torrent::connection_manager()->resolver()(
    host,
    (int)torrent::utils::socket_address::pf_unspec,
    SOCK_STREAM,
    call_add_d_peer_t(download, port));
}

torrent::Object
d_chunks_seen(core::Download* download) {
  const uint8_t* seen = download->download()->chunks_seen();

  if (seen == nullptr)
    return std::string();

  uint32_t size = download->download()->file_list()->size_chunks();

  std::string result;
  result.resize(size * 2);

  torrent::utils::transform_hex(
    (const char*)seen, (const char*)seen + size, result.begin());
  return result;
}

torrent::Object
f_multicall(core::Download* download, const torrent::Object::list_type& args) {
  if (args.empty())
    throw torrent::input_error("Too few arguments.");

  // We ignore the first arg for now, but it will be used for
  // selecting what files to include.

  // Add some pre-parsing of the commands, so we don't spend time
  // parsing and searching command map for every single call.
  torrent::Object             resultRaw = torrent::Object::create_list();
  torrent::Object::list_type& result    = resultRaw.as_list();
  std::vector<std::string>    regex_list;

  bool use_regex = true;

  if (args.front().is_list())
    std::transform(args.front().as_list().begin(),
                   args.front().as_list().end(),
                   std::back_inserter(regex_list),
                   [](const auto& object) { return object.as_string_c(); });
  else if (args.front().is_string() && !args.front().as_string().empty())
    regex_list.push_back(args.front().as_string());
  else
    use_regex = false;

  for (torrent::FileList::const_iterator itr  = download->file_list()->begin(),
                                         last = download->file_list()->end();
       itr != last;
       itr++) {
    if (use_regex &&
        std::find_if(
          regex_list.begin(), regex_list.end(), [itr](std::string pattern) {
            bool isAMatch = false;
            try {
              std::regex re(pattern);
              isAMatch = std::regex_match((*itr)->path()->as_string(), re);
            } catch (const std::regex_error& e) {
              control->core()->push_log_std("regex_error: " +
                                            std::string(e.what()));
            }
            return isAMatch;
          }) == regex_list.end())
      continue;

    torrent::Object::list_type& row =
      result.insert(result.end(), torrent::Object::create_list())->as_list();

    for (torrent::Object::list_const_iterator cItr = ++args.begin();
         cItr != args.end();
         cItr++) {
      const std::string& cmd = cItr->as_string();
      row.push_back(rpc::parse_command(rpc::make_target(*itr),
                                       cmd.c_str(),
                                       cmd.c_str() + cmd.size())
                      .first);
    }
  }

  return resultRaw;
}

torrent::Object
t_multicall(core::Download* download, const torrent::Object::list_type& args) {
  if (args.empty())
    throw torrent::input_error("Too few arguments.");

  // We ignore the first arg for now, but it will be used for
  // selecting what files to include.

  // Add some pre-parsing of the commands, so we don't spend time
  // parsing and searching command map for every single call.
  torrent::Object             resultRaw = torrent::Object::create_list();
  torrent::Object::list_type& result    = resultRaw.as_list();

  for (int itr = 0, last = download->tracker_list()->size(); itr != last;
       itr++) {
    torrent::Object::list_type& row =
      result.insert(result.end(), torrent::Object::create_list())->as_list();

    for (torrent::Object::list_const_iterator cItr = ++args.begin();
         cItr != args.end();
         cItr++) {
      const std::string& cmd = cItr->as_string();
      torrent::Tracker*  t   = download->tracker_list()->at(itr);

      row.push_back(rpc::parse_command(rpc::make_target(t),
                                       cmd.c_str(),
                                       cmd.c_str() + cmd.size())
                      .first);
    }
  }

  return resultRaw;
}

torrent::Object
p_multicall(core::Download* download, const torrent::Object::list_type& args) {
  if (args.empty())
    throw torrent::input_error("Too few arguments.");

  // We ignore the first arg for now, but it will be used for
  // selecting what files to include.

  // Add some pre-parsing of the commands, so we don't spend time
  // parsing and searching command map for every single call.
  torrent::Object             resultRaw = torrent::Object::create_list();
  torrent::Object::list_type& result    = resultRaw.as_list();

  for (torrent::ConnectionList::const_iterator
         itr  = download->connection_list()->begin(),
         last = download->connection_list()->end();
       itr != last;
       itr++) {
    torrent::Object::list_type& row =
      result.insert(result.end(), torrent::Object::create_list())->as_list();

    for (torrent::Object::list_const_iterator cItr = ++args.begin();
         cItr != args.end();
         cItr++) {
      const std::string& cmd = cItr->as_string();

      row.push_back(rpc::parse_command(rpc::make_target(*itr),
                                       cmd.c_str(),
                                       cmd.c_str() + cmd.size())
                      .first);
    }
  }

  return resultRaw;
}

torrent::Object
p_call_target(const torrent::Object::list_type& args) {
  if (args.empty() || args.begin() + 1 == args.end() ||
      args.begin() + 2 == args.end())
    throw torrent::input_error("Too few arguments.");

  // We ignore the first arg for now, but it will be used for
  // selecting what files to include.

  // Add some pre-parsing of the commands, so we don't spend time
  // parsing and searching command map for every single call.
  torrent::Object::list_const_iterator itr = args.begin();

  core::Download* download =
    control->core()->download_list()->find_hex_ptr(itr++->as_string().c_str());
  const std::string& peer_id     = itr++->as_string();
  const std::string& command_key = itr++->as_string();

  torrent::HashString hash;

  if (peer_id.size() != 40 || torrent::hash_string_from_hex_c_str(
                                peer_id.c_str(), hash) == peer_id.c_str())
    throw torrent::input_error("Not a hash string.");

  torrent::ConnectionList::iterator peerItr =
    download->connection_list()->find(hash.c_str());

  if (peerItr == download->connection_list()->end())
    throw torrent::input_error("Could not find peer.");

  if (itr == args.end())
    return rpc::commands.call(command_key.c_str());

  if (itr + 1 == args.end())
    return rpc::commands.call(command_key.c_str(), *itr);

  return rpc::commands.call(
    command_key.c_str(), torrent::Object::create_list_range(itr, args.end()));
}

torrent::Object
download_tracker_insert(core::Download*                   download,
                        const torrent::Object::list_type& args) {
  if (args.size() != 2)
    throw torrent::input_error("Wrong argument count.");

  int64_t group;

  if (args.front().is_string())
    rpc::parse_whole_value_nothrow(args.front().as_string().c_str(), &group);
  else
    group = args.front().as_value();

  if (group < 0 || group > 32)
    throw torrent::input_error("Tracker group number invalid.");

  download->download()->tracker_list()->insert_url(
    group, args.back().as_string(), true);
  return torrent::Object();
}

//
// New download commands and macros:
//

torrent::Object&
download_get_variable(core::Download* download,
                      const char*     first_key,
                      const char*     second_key = nullptr) {
  if (second_key == nullptr)
    return download->bencode()->get_key(first_key);

  return download->bencode()->get_key(first_key).get_key(second_key);
}

torrent::Object
download_set_variable(core::Download*        download,
                      const torrent::Object& rawArgs,
                      const char*            first_key,
                      const char*            second_key = nullptr) {
  if (second_key == nullptr)
    return download->bencode()->get_key(first_key) =
             torrent::object_create_normal(rawArgs);

  return download->bencode()->get_key(first_key).get_key(second_key) =
           torrent::object_create_normal(rawArgs);
}

torrent::Object
download_set_variable_value(core::Download*                    download,
                            const torrent::Object::value_type& args,
                            const char*                        first_key,
                            const char* second_key = nullptr) {
  if (second_key == nullptr)
    return download->bencode()->get_key(first_key) = args;

  return download->bencode()->get_key(first_key).get_key(second_key) = args;
}

torrent::Object
download_set_variable_value_ifz(core::Download*                    download,
                                const torrent::Object::value_type& args,
                                const char*                        first_key,
                                const char* second_key = nullptr) {
  torrent::Object& object =
    second_key == nullptr
      ? download->bencode()->get_key(first_key)
      : download->bencode()->get_key(first_key).get_key(second_key);

  if (object.as_value() == 0)
    object = args;

  return object;
}

torrent::Object
download_set_variable_string(core::Download*                     download,
                             const torrent::Object::string_type& args,
                             const char*                         first_key,
                             const char* second_key = nullptr) {
  if (second_key == nullptr)
    return download->bencode()->get_key(first_key) = args;

  return download->bencode()->get_key(first_key).get_key(second_key) = args;
}

//
//
//

torrent::Object
d_list_push_back(core::Download*        download,
                 const torrent::Object& rawArgs,
                 const char*            first_key,
                 const char*            second_key) {
  download_get_variable(download, first_key, second_key)
    .as_list()
    .push_back(rawArgs);

  return torrent::Object();
}

torrent::Object
d_list_push_back_unique(core::Download*        download,
                        const torrent::Object& rawArgs,
                        const char*            first_key,
                        const char*            second_key) {
  const torrent::Object& args =
    (rawArgs.is_list() && !rawArgs.as_list().empty())
      ? rawArgs.as_list().front()
      : rawArgs;
  torrent::Object::list_type& list =
    download_get_variable(download, first_key, second_key).as_list();

  if (std::find_if(list.begin(), list.end(), [args](torrent::Object& o) {
        return torrent::object_equal(args, o);
      }) == list.end())
    list.push_back(rawArgs);

  return torrent::Object();
}

torrent::Object
d_list_has(core::Download*        download,
           const torrent::Object& rawArgs,
           const char*            first_key,
           const char*            second_key) {
  const torrent::Object& args =
    (rawArgs.is_list() && !rawArgs.as_list().empty())
      ? rawArgs.as_list().front()
      : rawArgs;
  torrent::Object::list_type& list =
    download_get_variable(download, first_key, second_key).as_list();

  return (
    int64_t)(std::find_if(list.begin(), list.end(), [args](torrent::Object& o) {
               return torrent::object_equal(args, o);
             }) != list.end());
}

torrent::Object
d_list_remove(core::Download*        download,
              const torrent::Object& rawArgs,
              const char*            first_key,
              const char*            second_key) {
  const torrent::Object& args =
    (rawArgs.is_list() && !rawArgs.as_list().empty())
      ? rawArgs.as_list().front()
      : rawArgs;
  torrent::Object::list_type& list =
    download_get_variable(download, first_key, second_key).as_list();

  list.erase(std::remove_if(list.begin(),
                            list.end(),
                            [args](torrent::Object& o) {
                              return torrent::object_equal(args, o);
                            }),
             list.end());

  return torrent::Object();
}

#define CMD2_ON_INFO(func)                                                     \
  [](const auto& download, const auto&) { return download->info()->func(); }
#define CMD2_ON_DATA(func)                                                     \
  [](const auto& download, const auto&) { return download->data()->func(); }
#define CMD2_ON_DL(func)                                                       \
  [](const auto& download, const auto&) { return download->download()->func(); }
#define CMD2_ON_FL(func)                                                       \
  [](const auto& download, const auto&) {                                      \
    return download->file_list()->func();                                      \
  }

#define CMD2_DL_VAR_VALUE(key, first_key, second_key)                          \
  CMD2_DL(key, [](const auto& download, const auto&) {                         \
    return download_get_variable(download, first_key, second_key);             \
  });                                                                          \
  CMD2_DL_VALUE_P(key ".set", [](const auto& download, const auto& args) {     \
    return download_set_variable_value(download, args, first_key, second_key); \
  });

#define CMD2_DL_VAR_VALUE_PUBLIC(key, first_key, second_key)                   \
  CMD2_DL(key, [](const auto& download, const auto&) {                         \
    return download_get_variable(download, first_key, second_key);             \
  });                                                                          \
  CMD2_DL_VALUE(key ".set", [](const auto& download, const auto& args) {       \
    return download_set_variable_value(download, args, first_key, second_key); \
  });

#define CMD2_DL_TIMESTAMP(key, first_key, second_key)                          \
  CMD2_DL(key, [](const auto& download, const auto&) {                         \
    return download_get_variable(download, first_key, second_key);             \
  });                                                                          \
  CMD2_DL_VALUE_P(key ".set", [](const auto& download, const auto& args) {     \
    return download_set_variable_value(download, args, first_key, second_key); \
  });                                                                          \
  CMD2_DL_VALUE_P(key ".set_if_z",                                             \
                  [](const auto& download, const auto& args) {                 \
                    return download_set_variable_value_ifz(                    \
                      download, args, first_key, second_key);                  \
                  });

#define CMD2_DL_VAR_STRING(key, first_key, second_key)                         \
  CMD2_DL(key, [](const auto& download, const auto&) {                         \
    return download_get_variable(download, first_key, second_key);             \
  });                                                                          \
  CMD2_DL_STRING_P(key ".set", [](const auto& download, const auto& args) {    \
    return download_set_variable_string(                                       \
      download, args, first_key, second_key);                                  \
  });

#define CMD2_DL_VAR_STRING_PUBLIC(key, first_key, second_key)                  \
  CMD2_DL(key, [](const auto& download, const auto&) {                         \
    return download_get_variable(download, first_key, second_key);             \
  });                                                                          \
  CMD2_DL_STRING(key ".set", [](const auto& download, const auto& args) {      \
    return download_set_variable_string(                                       \
      download, args, first_key, second_key);                                  \
  });

int64_t
cg_d_group(core::Download* download);
const std::string&
cg_d_group_name(core::Download* download);
void
cg_d_group_set(core::Download* download, const torrent::Object& arg);

void
initialize_command_download() {
  CMD2_DL("d.hash", [](const auto& download, const auto&) {
    return torrent::utils::transform_hex_str(download->info()->hash());
  });
  CMD2_DL("d.local_id", [](const auto& download, const auto&) {
    return torrent::utils::transform_hex_str(download->info()->local_id());
  });
  CMD2_DL("d.local_id_html", [](const auto& download, const auto&) {
    return torrent::utils::copy_escape_html_str(download->info()->local_id());
  });
  CMD2_DL("d.bitfield", [](const auto& download, const auto&) {
    return retrieve_d_bitfield(download);
  });
  CMD2_DL("d.base_path", [](const auto& download, const auto&) {
    return retrieve_d_base_path(download);
  });
  CMD2_DL("d.base_filename", [](const auto& download, const auto&) {
    return retrieve_d_base_filename(download);
  });

  CMD2_DL("d.name", CMD2_ON_INFO(name));
  CMD2_DL("d.creation_date", CMD2_ON_INFO(creation_date));
  CMD2_DL("d.load_date", CMD2_ON_INFO(load_date));

  //
  // Network related:
  //

  CMD2_DL("d.up.rate", [](const auto& download, const auto&) {
    return download->info()->up_rate()->rate();
  });
  CMD2_DL("d.up.total", [](const auto& download, const auto&) {
    return download->info()->up_rate()->total();
  });
  CMD2_DL("d.down.rate", [](const auto& download, const auto&) {
    return download->info()->down_rate()->rate();
  });
  CMD2_DL("d.down.total", [](const auto& download, const auto&) {
    return download->info()->down_rate()->total();
  });
  CMD2_DL("d.skip.rate", [](const auto& download, const auto&) {
    return download->info()->skip_rate()->rate();
  });
  CMD2_DL("d.skip.total", [](const auto& download, const auto&) {
    return download->info()->skip_rate()->total();
  });

  CMD2_DL("d.peer_exchange", CMD2_ON_INFO(is_pex_enabled));
  CMD2_DL_VALUE_V("d.peer_exchange.set",
                  [](const auto& download, const auto& v) {
                    return download->download()->set_pex_enabled(v);
                  });

  CMD2_DL_LIST("d.create_link", [](const auto& download, const auto& args) {
    return apply_d_change_link(download, args, 0);
  });
  CMD2_DL_LIST("d.delete_link", [](const auto& download, const auto& args) {
    return apply_d_change_link(download, args, 1);
  });
  CMD2_DL("d.delete_tied", [](const auto& download, const auto&) {
    return apply_d_delete_tied(download);
  });

  CMD2_FUNC_SINGLE("d.start",
                   "d.hashing_failed.set=0 ;view.set_visible=started");
  CMD2_FUNC_SINGLE("d.stop", "view.set_visible=stopped");
  CMD2_FUNC_SINGLE("d.try_start",
                   "branch=\"or={d.hashing_failed=,d.ignore_commands=}\",{},{"
                   "view.set_visible=started}");
  CMD2_FUNC_SINGLE("d.try_stop",
                   "branch=d.ignore_commands=, {}, {view.set_visible=stopped}");
  CMD2_FUNC_SINGLE(
    "d.try_close",
    "branch=d.ignore_commands=, {}, {view.set_visible=stopped, d.close=}");

  //
  // Control functinos:
  //

  CMD2_DL("d.is_open", CMD2_ON_INFO(is_open));
  CMD2_DL("d.is_active", CMD2_ON_INFO(is_active));
  CMD2_DL("d.is_hash_checked", [](const auto& download, const auto&) {
    return download->download()->is_hash_checked();
  });
  CMD2_DL("d.is_hash_checking", [](const auto& download, const auto&) {
    return download->download()->is_hash_checking();
  });
  CMD2_DL("d.is_multi_file", [](const auto& download, const auto&) {
    return download->file_list()->is_multi_file();
  });
  CMD2_DL("d.is_private", CMD2_ON_INFO(is_private));
  CMD2_DL("d.is_pex_active", CMD2_ON_INFO(is_pex_active));
  CMD2_DL("d.is_partially_done", CMD2_ON_DATA(is_partially_done));
  CMD2_DL("d.is_not_partially_done", CMD2_ON_DATA(is_not_partially_done));
  CMD2_DL("d.is_meta", CMD2_ON_INFO(is_meta_download));

  CMD2_DL_V("d.resume", [](const auto& download, const auto&) {
    return control->core()->download_list()->resume_default(download);
  });
  CMD2_DL_V("d.pause", [](const auto& download, const auto&) {
    return control->core()->download_list()->pause_default(download);
  });
  CMD2_DL_V("d.open", [](const auto& download, const auto&) {
    return control->core()->download_list()->open_throw(download);
  });
  CMD2_DL_V("d.close", [](const auto& download, const auto&) {
    return control->core()->download_list()->close_throw(download);
  });
  CMD2_DL_V("d.close.directly", [](const auto& download, const auto&) {
    return control->core()->download_list()->close_directly(download);
  });
  CMD2_DL_V("d.erase", [](const auto& download, const auto&) {
    return control->core()->download_list()->erase_ptr(download);
  });
  CMD2_DL_V("d.check_hash", [](const auto& download, const auto&) {
    return control->core()->download_list()->check_hash(download);
  });
  CMD2_DL("d.save_resume", [](const auto& download, const auto&) {
    return control->core()->download_store()->save_resume(download);
  });
  CMD2_DL("d.save_full_session", [](const auto& download, const auto&) {
    return control->core()->download_store()->save_full(download);
  });

  CMD2_DL_V("d.update_priorities", CMD2_ON_DL(update_priorities));

  CMD2_DL_STRING_V("add_peer", [](const auto& download, const auto& arg) {
    return apply_d_add_peer(download, arg);
  });

  //
  // Custom settings:
  //

  CMD2_DL_STRING("d.custom", [](const auto& download, const auto& key) {
    return retrieve_d_custom(download, key);
  });
  CMD2_DL_STRING("d.custom_throw", [](const auto& download, const auto& key) {
    return retrieve_d_custom_throw(download, key);
  });
  CMD2_DL_LIST("d.custom.set", [](const auto& download, const auto& args) {
    return apply_d_custom(download, args);
  });
  CMD2_DL_LIST("d.custom.if_z", [](const auto& download, const auto& args) {
    return retrieve_d_custom_if_z(download, args);
  });
  CMD2_DL_LIST("d.custom.keys", [](const auto& download, const auto& args) {
    return retrieve_d_custom_map(download, true, args);
  });
  CMD2_DL_LIST("d.custom.items", [](const auto& download, const auto& args) {
    return retrieve_d_custom_map(download, false, args);
  });

  CMD2_DL_VAR_STRING_PUBLIC("d.custom1", "rtorrent", "custom1");
  CMD2_DL_VAR_STRING_PUBLIC("d.custom2", "rtorrent", "custom2");
  CMD2_DL_VAR_STRING_PUBLIC("d.custom3", "rtorrent", "custom3");
  CMD2_DL_VAR_STRING_PUBLIC("d.custom4", "rtorrent", "custom4");
  CMD2_DL_VAR_STRING_PUBLIC("d.custom5", "rtorrent", "custom5");

  // 0 - stopped
  // 1 - started
  CMD2_DL_VAR_VALUE("d.state", "rtorrent", "state");
  CMD2_DL_VAR_VALUE("d.complete", "rtorrent", "complete");

  CMD2_FUNC_SINGLE("d.incomplete", "not=(d.complete)");

  // 0 off
  // 1 scheduled, being controlled by a download scheduler. Includes a priority.
  // 3 forced off
  // 2 forced on
  CMD2_DL_VAR_VALUE("d.mode", "rtorrent", "mode");

  // 0 - Not hashing
  // 1 - Normal hashing
  // 2 - Download finished, hashing
  // 3 - Rehashing
  CMD2_DL_VAR_VALUE("d.hashing", "rtorrent", "hashing");

  // 'tied_to_file' is the file the download is associated with, and
  // can be changed by the user.
  //
  // 'loaded_file' is the file this instance of the torrent was loaded
  // from, and should not be changed.
  CMD2_DL_VAR_STRING_PUBLIC("d.tied_to_file", "rtorrent", "tied_to_file");
  CMD2_DL_VAR_STRING("d.loaded_file", "rtorrent", "loaded_file");

  // The "state_changed" variable is required to be a valid unix time
  // value, it indicates the last time the torrent changed its state,
  // resume/pause.
  CMD2_DL_VAR_VALUE("d.state_changed", "rtorrent", "state_changed");
  CMD2_DL_VAR_VALUE("d.state_counter", "rtorrent", "state_counter");
  CMD2_DL_VAR_VALUE_PUBLIC("d.ignore_commands", "rtorrent", "ignore_commands");

  CMD2_DL_TIMESTAMP("d.timestamp.started", "rtorrent", "timestamp.started");
  CMD2_DL_TIMESTAMP("d.timestamp.finished", "rtorrent", "timestamp.finished");
  CMD2_DL_TIMESTAMP(
    "d.timestamp.last_active", "rtorrent", "timestamp.last_active");

  CMD2_DL("d.connection_current", [](const auto& download, const auto&) {
    return torrent::option_as_string(torrent::OPTION_CONNECTION_TYPE,
                                     download->download()->connection_type());
  });
  CMD2_DL_STRING("d.connection_current.set",
                 [](const auto& download, const auto& name) {
                   return apply_d_connection_type(download, name);
                 });

  CMD2_DL_VAR_STRING_PUBLIC(
    "d.connection_leech", "rtorrent", "connection_leech");
  CMD2_DL_VAR_STRING_PUBLIC("d.connection_seed", "rtorrent", "connection_seed");

  CMD2_DL("d.up.choke_heuristics", [](const auto& download, const auto&) {
    return torrent::option_as_string(
      torrent::OPTION_CHOKE_HEURISTICS,
      download->download()->upload_choke_heuristic());
  });
  CMD2_DL_STRING("d.up.choke_heuristics.set",
                 [](const auto& download, const auto& name) {
                   return apply_d_choke_heuristics(download, name, false);
                 });
  CMD2_DL("d.down.choke_heuristics", [](const auto& download, const auto&) {
    return torrent::option_as_string(
      torrent::OPTION_CHOKE_HEURISTICS,
      download->download()->download_choke_heuristic());
  });
  CMD2_DL_STRING("d.down.choke_heuristics.set",
                 [](const auto& download, const auto& name) {
                   return apply_d_choke_heuristics(download, name, true);
                 });

  CMD2_DL_VAR_STRING(
    "d.up.choke_heuristics.leech", "rtorrent", "choke_heuristics.up.leech");
  CMD2_DL_VAR_STRING(
    "d.up.choke_heuristics.seed", "rtorrent", "choke_heuristics.up.seed");
  CMD2_DL_VAR_STRING(
    "d.down.choke_heuristics.leech", "rtorrent", "choke_heuristics.down.leech");
  CMD2_DL_VAR_STRING(
    "d.down.choke_heuristics.seed", "rtorrent", "choke_heuristics.down.seed");

  CMD2_DL("d.down.sequential", CMD2_ON_DL(is_sequential_enabled));
  CMD2_DL_VALUE_V("d.down.sequential.set",
                  [](const auto& download, const auto& v) {
                    return download->download()->set_sequential_enabled(v);
                  });

  CMD2_DL("d.hashing_failed", [](const auto& download, const auto&) {
    return download->is_hash_failed();
  });
  CMD2_DL_VALUE_V("d.hashing_failed.set",
                  [](const auto& download, const auto& v) {
                    return download->set_hash_failed(v);
                  });

  CMD2_DL("d.views", [](const auto& download, const auto&) {
    return download_get_variable(download, "rtorrent", "views");
  });
  CMD2_DL("d.views.has", [](const auto& download, const auto& rawArgs) {
    return d_list_has(download, rawArgs, "rtorrent", "views");
  });
  CMD2_DL("d.views.remove", [](const auto& download, const auto& rawArgs) {
    return d_list_remove(download, rawArgs, "rtorrent", "views");
  });
  CMD2_DL("d.views.push_back", [](const auto& download, const auto& rawArgs) {
    return d_list_push_back(download, rawArgs, "rtorrent", "views");
  });
  CMD2_DL(
    "d.views.push_back_unique", [](const auto& download, const auto& rawArgs) {
      return d_list_push_back_unique(download, rawArgs, "rtorrent", "views");
    });

  // This command really needs to be improved, so we have proper
  // logging support.
  CMD2_DL("d.message", [](const auto& download, const auto&) {
    return download->message();
  });
  CMD2_DL_STRING_V("d.message.set", [](const auto& download, const auto& msg) {
    return download->set_message(msg);
  });

  CMD2_DL("d.max_file_size", CMD2_ON_FL(max_file_size));
  CMD2_DL_VALUE_V("d.max_file_size.set",
                  [](const auto& download, const auto& v) {
                    return download->file_list()->set_max_file_size(v);
                  });

  CMD2_DL("d.peers_min", [](const auto& download, const auto&) {
    return download->connection_list()->min_size();
  });
  CMD2_DL_VALUE_V("d.peers_min.set", [](const auto& download, const auto& v) {
    return download->connection_list()->set_min_size(v);
  });
  CMD2_DL("d.peers_max", [](const auto& download, const auto&) {
    return download->connection_list()->max_size();
  });
  CMD2_DL_VALUE_V("d.peers_max.set", [](const auto& download, const auto& v) {
    return download->connection_list()->set_max_size(v);
  });
  CMD2_DL("d.uploads_max", [](const auto& download, const auto&) {
    return download->download()->uploads_max();
  });
  CMD2_DL_VALUE_V("d.uploads_max.set", [](const auto& download, const auto& v) {
    return download->download()->set_uploads_max(v);
  });
  CMD2_DL("d.uploads_min", [](const auto& download, const auto&) {
    return download->download()->uploads_min();
  });
  CMD2_DL_VALUE_V("d.uploads_min.set", [](const auto& download, const auto& v) {
    return download->download()->set_uploads_min(v);
  });
  CMD2_DL("d.downloads_max", [](const auto& download, const auto&) {
    return download->download()->downloads_max();
  });
  CMD2_DL_VALUE_V("d.downloads_max.set",
                  [](const auto& download, const auto& v) {
                    return download->download()->set_downloads_max(v);
                  });
  CMD2_DL("d.downloads_min", [](const auto& download, const auto&) {
    return download->download()->downloads_min();
  });
  CMD2_DL_VALUE_V("d.downloads_min.set",
                  [](const auto& download, const auto& v) {
                    return download->download()->set_downloads_min(v);
                  });
  CMD2_DL("d.peers_connected", [](const auto& download, const auto&) {
    return download->connection_list()->size();
  });
  CMD2_DL("d.peers_not_connected", [](const auto& download, const auto&) {
    return download->c_peer_list()->available_list_size();
  });

  CMD2_DL("d.peers_complete", CMD2_ON_DL(peers_complete));
  CMD2_DL("d.peers_accounted", CMD2_ON_DL(peers_accounted));

  CMD2_DL_V("d.disconnect.seeders", [](const auto& download, const auto&) {
    return download->connection_list()->erase_seeders();
  });

  CMD2_DL("d.accepting_seeders", CMD2_ON_INFO(is_accepting_seeders));
  CMD2_DL_V("d.accepting_seeders.enable",
            [](const auto& download, const auto&) {
              return download->info()->public_set_flags(
                torrent::DownloadInfo::flag_accepting_seeders);
            });
  CMD2_DL_V("d.accepting_seeders.disable",
            [](const auto& download, const auto&) {
              return download->info()->public_unset_flags(
                torrent::DownloadInfo::flag_accepting_seeders);
            });

  CMD2_DL("d.throttle_name", [](const auto& download, const auto&) {
    return download_get_variable(download, "rtorrent", "throttle_name");
  });
  CMD2_DL_STRING_V("d.throttle_name.set",
                   [](const auto& download, const auto& name) {
                     return download->set_throttle_name(name);
                   });

  CMD2_DL("d.bytes_done", CMD2_ON_DL(bytes_done));
  CMD2_DL("d.ratio", [](const auto& download, const auto&) {
    return retrieve_d_ratio(download);
  });
  CMD2_DL("d.chunks_hashed", CMD2_ON_DL(chunks_hashed));
  CMD2_DL("d.free_diskspace", CMD2_ON_FL(free_diskspace));

  CMD2_DL("d.size_files", CMD2_ON_FL(size_files));
  CMD2_DL("d.size_bytes", CMD2_ON_FL(size_bytes));
  CMD2_DL("d.size_chunks", CMD2_ON_FL(size_chunks));
  CMD2_DL("d.chunk_size", CMD2_ON_FL(chunk_size));
  CMD2_DL("d.size_pex", CMD2_ON_DL(size_pex));
  CMD2_DL("d.max_size_pex", CMD2_ON_DL(max_size_pex));

  CMD2_DL("d.chunks_seen", [](const auto& download, const auto&) {
    return d_chunks_seen(download);
  });

  CMD2_DL("d.completed_bytes", CMD2_ON_FL(completed_bytes));
  CMD2_DL("d.completed_chunks", CMD2_ON_FL(completed_chunks));
  CMD2_DL("d.left_bytes", CMD2_ON_FL(left_bytes));

  CMD2_DL("d.wanted_chunks", CMD2_ON_DATA(wanted_chunks));

  // Do not exposre d.tracker_announce.force to regular users.
  CMD2_DL_V("d.tracker_announce", [](const auto& download, const auto&) {
    return download->download()->manual_request(false);
  });
  CMD2_DL_V("d.tracker_announce.force", [](const auto& download, const auto&) {
    return download->download()->manual_request(true);
  });

  CMD2_DL("d.tracker_numwant", [](const auto& download, const auto&) {
    return download->tracker_list()->numwant();
  });
  CMD2_DL_VALUE_V("d.tracker_numwant.set",
                  [](const auto& download, const auto& v) {
                    return download->tracker_list()->set_numwant(v);
                  });
  // TODO: Deprecate 'd.tracker_focus'.
  CMD2_DL("d.tracker_focus", [](const auto& download, const auto&) {
    return download->tracker_list_size();
  });
  CMD2_DL("d.tracker_size", [](const auto& download, const auto&) {
    return download->tracker_list_size();
  });

  CMD2_DL_LIST("d.tracker.insert", [](const auto& download, const auto& args) {
    return download_tracker_insert(download, args);
  });
  CMD2_DL_VALUE_V("d.tracker.send_scrape",
                  [](const auto& download, const auto& v) {
                    return download->tracker_controller()->scrape_request(v);
                  });

  CMD2_DL("d.directory", CMD2_ON_FL(root_dir));
  CMD2_DL_STRING_V("d.directory.set",
                   [](const auto& download, const auto& name) {
                     return apply_d_directory(download, name);
                   });
  CMD2_DL("d.directory_base", CMD2_ON_FL(root_dir));
  CMD2_DL_STRING_V("d.directory_base.set",
                   [](const auto& download, const auto& name) {
                     return download->set_root_directory(name);
                   });

  CMD2_DL("d.priority", [](const auto& download, const auto&) {
    return download->priority();
  });
  CMD2_DL("d.priority_str", [](const auto& download, const auto&) {
    return retrieve_d_priority_str(download);
  });
  CMD2_DL_VALUE_V("d.priority.set", [](const auto& download, const auto& p) {
    return download->set_priority(p);
  });

  CMD2_DL("d.group", [](const auto& download, const auto&) {
    return cg_d_group(download);
  });
  CMD2_DL("d.group.name", [](const auto& download, const auto&) {
    return cg_d_group(download);
  });
  CMD2_DL_V("d.group.set", [](const auto& download, const auto& arg) {
    return cg_d_group_set(download, arg);
  });

  CMD2_DL_LIST("f.multicall", [](const auto& download, const auto& args) {
    return f_multicall(download, args);
  });
  CMD2_DL_LIST("p.multicall", [](const auto& download, const auto& args) {
    return p_multicall(download, args);
  });
  CMD2_DL_LIST("t.multicall", [](const auto& download, const auto& args) {
    return t_multicall(download, args);
  });

  CMD2_ANY_LIST("p.call_target", [](const auto&, const auto& args) {
    return p_call_target(args);
  });
}
