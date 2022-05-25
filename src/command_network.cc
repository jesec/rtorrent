// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#include <cstdio>
#include <filesystem>
#include <fstream>
#include <functional>
#include <limits>
#include <torrent/common.h>
#include <unistd.h>

#include <torrent/connection_manager.h>
#include <torrent/data/file_manager.h>
#include <torrent/download/resource_manager.h>
#include <torrent/rate.h>
#include <torrent/torrent.h>
#include <torrent/tracker.h>
#include <torrent/tracker_list.h>
#include <torrent/utils/address_info.h>
#include <torrent/utils/log.h>
#include <torrent/utils/option_strings.h>
#include <torrent/utils/path.h>

#include "core/download.h"
#include "core/manager.h"
#include "rpc/parse.h"
#include "rpc/parse_commands.h"
#include "rpc/scgi.h"
#include "ui/root.h"

#include "command_helpers.h"
#include "control.h"
#include "globals.h"

torrent::Object
apply_encryption(const torrent::Object::list_type& args) {
  uint32_t options_mask = torrent::ConnectionManager::encryption_none;

  for (torrent::Object::list_const_iterator itr  = args.begin(),
                                            last = args.end();
       itr != last;
       itr++) {
    uint32_t opt = torrent::option_find_string(torrent::OPTION_ENCRYPTION,
                                               itr->as_string().c_str());

    if (opt == torrent::ConnectionManager::encryption_none)
      options_mask = torrent::ConnectionManager::encryption_none;
    else
      options_mask |= opt;
  }

  torrent::connection_manager()->set_encryption_options(options_mask);

  return torrent::Object();
}

torrent::Object
apply_tos(const torrent::Object::string_type& arg) {
  rpc::command_base::value_type value;

  if (!rpc::parse_whole_value_nothrow(arg.c_str(), &value, 16, 1))
    value = torrent::option_find_string(torrent::OPTION_IP_TOS, arg.c_str());

  torrent::connection_manager()->set_priority(value);

  return torrent::Object();
}

torrent::Object
apply_encoding_list(const std::string& arg) {
  torrent::encoding_list()->push_back(arg);
  return torrent::Object();
}

torrent::File*
rpc_find_file(core::Download* download, uint32_t index) {
  if (index >= download->file_list()->size_files())
    return nullptr;

  return download->file_list()->at(index);
}

// Ergh... time to update the Tracker API to allow proper ptrs.
torrent::Tracker*
rpc_find_tracker(core::Download* download, uint32_t index) {
  if (index >= download->tracker_list()->size())
    return nullptr;

  return download->tracker_list()->at(index);
}

torrent::Peer*
rpc_find_peer(core::Download* download, const torrent::HashString& hash) {
  torrent::ConnectionList::iterator itr =
    download->connection_list()->find(hash.c_str());

  if (itr == download->connection_list()->end())
    return nullptr;

  return *itr;
}

void
initialize_rpc() {
  rpc::rpc.initialize(
    [](const char* hash) {
      return control->core()->download_list()->find_hex_ptr(hash);
    },
    [](core::Download* d, uint32_t index) { return rpc_find_file(d, index); },
    [](core::Download* d, uint32_t index) {
      return rpc_find_tracker(d, index);
    },
    [](core::Download* d, const torrent::HashString& hash) {
      return rpc_find_peer(d, hash);
    });

  unsigned int count = 0;

  for (rpc::CommandMap::const_iterator itr  = rpc::commands.begin(),
                                       last = rpc::commands.end();
       itr != last;
       itr++, count++) {
    if (!(itr->second.m_flags & rpc::CommandMap::flag_public))
      continue;

    rpc::rpc.insert_command(itr->first, itr->second.m_parm, itr->second.m_doc);
  }

  lt_log_print(
    torrent::LOG_RPC_EVENTS, "XMLRPC initialized with %u functions.", count);
}

torrent::Object
apply_scgi(const std::string& arg, int type) {
  if (worker_thread->scgi() != nullptr)
    throw torrent::input_error("SCGI already enabled.");

  if (!rpc::rpc.is_initialized())
    initialize_rpc();

  rpc::SCgi* scgi = new rpc::SCgi;

  torrent::utils::address_info*   ai = nullptr;
  torrent::utils::socket_address  sa;
  torrent::utils::socket_address* saPtr;

  try {
    int         port, err;
    char        dummy;
    char        address[1024];
    std::string path;

    switch (type) {
      case 1:
        if (std::sscanf(arg.c_str(), ":%i%c", &port, &dummy) == 1) {
          sa.sa_inet()->clear();
          saPtr = &sa;

          lt_log_print(
            torrent::LOG_RPC_EVENTS,
            "SCGI socket is open to any address and is a security risk");

        } else if (std::sscanf(
                     arg.c_str(), "%1023[^:]:%i%c", address, &port, &dummy) ==
                     2 ||
                   std::sscanf(
                     arg.c_str(), "[%64[^]]]:%i%c", address, &port, &dummy) ==
                     2) { // [xx::xx]:port format
          if ((err = torrent::utils::address_info::get_address_info(
                 address, PF_UNSPEC, SOCK_STREAM, &ai)) != 0)
            throw torrent::input_error(
              "Could not bind address: " +
              std::string(torrent::utils::address_info::strerror(err)) + ".");

          saPtr = ai->address();

          lt_log_print(
            torrent::LOG_RPC_EVENTS,
            "SCGI socket is bound to an address and might be a security risk");

        } else {
          throw torrent::input_error("Could not parse address.");
        }

        if (port <= 0 || port >= (1 << 16))
          throw torrent::input_error("Invalid port number.");

        saPtr->set_port(port);
        scgi->open_port(saPtr,
                        saPtr->length(),
                        rpc::call_command_value("network.scgi.dont_route"));

        break;

      case 2:
      default:
        path = torrent::utils::path_expand(arg);

        // Try to avoid removing socket opened by another instance
        if (std::filesystem::is_socket(path) &&
            std::filesystem::exists("/proc/net/unix")) {
          try {
            auto        list = std::ifstream("/proc/net/unix");
            std::string entry;
            while (std::getline(list, entry)) {
              if (entry.find(path) != std::string::npos) {
                throw torrent::input_error("Socket already in use.");
              }
            }
          } catch (std::ios_base::failure&) {
            // do nothing.
          }
        }

        unlink(path.c_str());
        scgi->open_named(path);

        break;
    }

    if (ai != nullptr)
      torrent::utils::address_info::free_address_info(ai);

  } catch (torrent::local_error& e) {
    if (ai != nullptr)
      torrent::utils::address_info::free_address_info(ai);

    delete scgi;
    throw torrent::input_error(e.what());
  }

  worker_thread->set_scgi(scgi);
  return torrent::Object();
}

void
initialize_command_network() {
  torrent::ConnectionManager* cm          = torrent::connection_manager();
  torrent::FileManager*       fileManager = torrent::file_manager();
  core::CurlStack*            httpStack   = control->core()->http_stack();

  CMD2_ANY_STRING("encoding.add", [](const auto&, const auto& arg) {
    return apply_encoding_list(arg);
  });

  // Isn't port_open used?
  CMD2_VAR_BOOL("network.port_open", true);
  CMD2_VAR_BOOL("network.port_random", true);
  CMD2_VAR_STRING("network.port_range", "6881-6999");

  CMD2_ANY("network.listen.port",
           [cm](const auto&, const auto&) { return cm->listen_port(); });
  CMD2_ANY("network.listen.backlog",
           [cm](const auto&, const auto&) { return cm->listen_backlog(); });
  CMD2_ANY_VALUE_V(
    "network.listen.backlog.set",
    [cm](const auto&, const auto& v) { return cm->set_listen_backlog(v); });

  CMD2_VAR_BOOL("protocol.pex", true);
  CMD2_ANY_LIST("protocol.encryption.set", [](const auto&, const auto& args) {
    return apply_encryption(args);
  });

  CMD2_VAR_STRING("protocol.connection.leech", "leech");
  CMD2_VAR_STRING("protocol.connection.seed", "seed");

  CMD2_VAR_STRING("protocol.choke_heuristics.up.leech", "upload_leech");
  CMD2_VAR_STRING("protocol.choke_heuristics.up.seed", "upload_leech");
  CMD2_VAR_STRING("protocol.choke_heuristics.down.leech", "download_leech");
  CMD2_VAR_STRING("protocol.choke_heuristics.down.seed", "download_leech");

  CMD2_ANY("network.http.cacert", [httpStack](const auto&, const auto&) {
    return httpStack->http_cacert();
  });
  CMD2_ANY_STRING_V("network.http.cacert.set",
                    [httpStack](const auto&, const auto& s) {
                      return httpStack->set_http_cacert(s);
                    });
  CMD2_ANY("network.http.capath", [httpStack](const auto&, const auto&) {
    return httpStack->http_capath();
  });
  CMD2_ANY_STRING_V("network.http.capath.set",
                    [httpStack](const auto&, const auto& s) {
                      return httpStack->set_http_capath(s);
                    });
  CMD2_ANY(
    "network.http.dns_cache_timeout",
    [httpStack](const auto&, const auto&) { return httpStack->dns_timeout(); });
  CMD2_ANY_VALUE_V("network.http.dns_cache_timeout.set",
                   [httpStack](const auto&, const auto& timeout) {
                     return httpStack->set_dns_timeout(timeout);
                   });
  CMD2_ANY("network.http.current_open", [httpStack](const auto&, const auto&) {
    return httpStack->active();
  });
  CMD2_ANY("network.http.max_open", [httpStack](const auto&, const auto&) {
    return httpStack->max_active();
  });
  CMD2_ANY_VALUE_V("network.http.max_open.set",
                   [httpStack](const auto&, const auto& a) {
                     return httpStack->set_max_active(a);
                   });
  CMD2_ANY("network.http.proxy_address", [httpStack](const auto&, const auto&) {
    return httpStack->http_proxy();
  });
  CMD2_ANY_STRING_V("network.http.proxy_address.set",
                    [httpStack](const auto&, const auto& s) {
                      return httpStack->set_http_proxy(s);
                    });
  CMD2_ANY("network.http.ssl_verify_host",
           [httpStack](const auto&, const auto&) {
             return httpStack->ssl_verify_host();
           });
  CMD2_ANY_VALUE_V("network.http.ssl_verify_host.set",
                   [httpStack](const auto&, const auto& v) {
                     return httpStack->set_ssl_verify_host(v);
                   });
  CMD2_ANY("network.http.ssl_verify_peer",
           [httpStack](const auto&, const auto&) {
             return httpStack->ssl_verify_peer();
           });
  CMD2_ANY_VALUE_V("network.http.ssl_verify_peer.set",
                   [httpStack](const auto&, const auto& v) {
                     return httpStack->set_ssl_verify_peer(v);
                   });

  CMD2_ANY("network.send_buffer.size",
           [cm](const auto&, const auto&) { return cm->send_buffer_size(); });
  CMD2_ANY_VALUE_V(
    "network.send_buffer.size.set",
    [cm](const auto&, const auto& v) { return cm->set_send_buffer_size(v); });
  CMD2_ANY("network.receive_buffer.size", [cm](const auto&, const auto&) {
    return cm->receive_buffer_size();
  });
  CMD2_ANY_VALUE_V("network.receive_buffer.size.set",
                   [cm](const auto&, const auto& v) {
                     return cm->set_receive_buffer_size(v);
                   });
  CMD2_ANY_STRING("network.tos.set",
                  [](const auto&, const auto& arg) { return apply_tos(arg); });

  CMD2_ANY("network.bind_address", [](const auto&, const auto&) {
    return control->core()->bind_address();
  });
  CMD2_ANY_STRING_V("network.bind_address.set",
                    [](const auto&, const auto& addr) {
                      return control->core()->set_bind_address(addr);
                    });
  CMD2_ANY("network.local_address", [](const auto&, const auto&) {
    return control->core()->local_address();
  });
  CMD2_ANY_STRING_V("network.local_address.set",
                    [](const auto&, const auto& addr) {
                      return control->core()->set_local_address(addr);
                    });
  CMD2_ANY("network.proxy_address", [](const auto&, const auto&) {
    return control->core()->proxy_address();
  });
  CMD2_ANY_STRING_V("network.proxy_address.set",
                    [](const auto&, const auto& addr) {
                      return control->core()->set_proxy_address(addr);
                    });

  CMD2_ANY("network.open_files", [fileManager](const auto&, const auto&) {
    return fileManager->open_files();
  });
  CMD2_ANY("network.max_open_files", [fileManager](const auto&, const auto&) {
    return fileManager->max_open_files();
  });
  CMD2_ANY_VALUE_V("network.max_open_files.set",
                   [fileManager](const auto&, const auto& v) {
                     return fileManager->set_max_open_files(v);
                   });
  CMD2_ANY("network.total_handshakes", [](const auto&, const auto&) {
    return torrent::total_handshakes();
  });
  CMD2_ANY("network.open_sockets",
           [cm](const auto&, const auto&) { return cm->size(); });
  CMD2_ANY("network.max_open_sockets",
           [cm](const auto&, const auto&) { return cm->max_size(); });
  CMD2_ANY_VALUE_V(
    "network.max_open_sockets.set",
    [cm](const auto&, const auto& v) { return cm->set_max_size(v); });

  CMD2_ANY_STRING("network.scgi.open_port", [](const auto&, const auto& arg) {
    return apply_scgi(arg, 1);
  });
  CMD2_ANY_STRING("network.scgi.open_local", [](const auto&, const auto& arg) {
    return apply_scgi(arg, 2);
  });
  CMD2_VAR_BOOL("network.scgi.dont_route", false);

  CMD2_ANY("network.xmlrpc.size_limit", [](const auto&, const auto&) {
    return std::numeric_limits<size_t>::max();
  });

  CMD2_REDIRECT_GENERIC("network.xmlrpc.dialect.set", "true");
  CMD2_REDIRECT_GENERIC("network.xmlrpc.size_limit.set", "true");
}
