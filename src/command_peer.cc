// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#include <torrent/bitfield.h>
#include <torrent/peer/connection_list.h>
#include <torrent/peer/peer.h>
#include <torrent/peer/peer_info.h>
#include <torrent/rate.h>
#include <torrent/utils/error_number.h>
#include <torrent/utils/path.h>
#include <torrent/utils/socket_address.h>
#include <torrent/utils/string_manip.h>

#include "core/manager.h"
#include "display/utils.h"

#include "command_helpers.h"
#include "control.h"
#include "globals.h"

torrent::Object
retrieve_p_id(torrent::Peer* peer) {
  const torrent::HashString* hashString = &peer->id();

  return torrent::utils::transform_hex(hashString->begin(), hashString->end());
}

torrent::Object
retrieve_p_id_html(torrent::Peer* peer) {
  const torrent::HashString* hashString = &peer->id();

  return torrent::utils::copy_escape_html(hashString->begin(),
                                          hashString->end());
}

torrent::Object
retrieve_p_address(torrent::Peer* peer) {
  const torrent::utils::socket_address* addr =
    torrent::utils::socket_address::cast_from(
      peer->peer_info()->socket_address());

  if (addr->family() == torrent::utils::socket_address::af_inet6)
    return "[" + addr->address_str() + "]";
  else
    return addr->address_str();
}

torrent::Object
retrieve_p_port(torrent::Peer* peer) {
  return torrent::utils::socket_address::cast_from(
           peer->peer_info()->socket_address())
    ->port();
}

torrent::Object
retrieve_p_client_version(torrent::Peer* peer) {
  char buf[128];
  display::print_client_version(
    buf, buf + 128, peer->peer_info()->client_info());

  return std::string(buf);
}

torrent::Object
retrieve_p_options_str(torrent::Peer* peer) {
  return torrent::utils::transform_hex(peer->peer_info()->options(),
                                       peer->peer_info()->options() + 8);
}

torrent::Object
retrieve_p_completed_percent(torrent::Peer* peer) {
  return (100 * peer->bitfield()->size_set()) / peer->bitfield()->size_bits();
}

void
initialize_command_peer() {
  CMD2_PEER("p.id",
            [](const auto& peer, const auto&) { return retrieve_p_id(peer); });
  CMD2_PEER("p.id_html", [](const auto& peer, const auto&) {
    return retrieve_p_id_html(peer);
  });
  CMD2_PEER("p.client_version", [](const auto& peer, const auto&) {
    return retrieve_p_client_version(peer);
  });

  CMD2_PEER("p.options_str", [](const auto& peer, const auto&) {
    return retrieve_p_options_str(peer);
  });

  CMD2_PEER("p.is_encrypted",
            [](const auto& peer, const auto&) { return peer->is_encrypted(); });
  CMD2_PEER("p.is_incoming",
            [](const auto& peer, const auto&) { return peer->is_incoming(); });
  CMD2_PEER("p.is_obfuscated", [](const auto& peer, const auto&) {
    return peer->is_obfuscated();
  });
  CMD2_PEER("p.is_snubbed",
            [](const auto& peer, const auto&) { return peer->is_snubbed(); });

  CMD2_PEER("p.is_unwanted", [](const auto& peer, const auto&) {
    return peer->peer_info()->is_unwanted();
  });
  CMD2_PEER("p.is_preferred", [](const auto& peer, const auto&) {
    return peer->peer_info()->is_preferred();
  });

  CMD2_PEER("p.address", [](const auto& peer, const auto&) {
    return retrieve_p_address(peer);
  });
  CMD2_PEER("p.port", [](const auto& peer, const auto&) {
    return retrieve_p_port(peer);
  });

  CMD2_PEER("p.completed_percent", [](const auto& peer, const auto&) {
    return retrieve_p_completed_percent(peer);
  });

  CMD2_PEER("p.up_rate", [](const auto& peer, const auto&) {
    return peer->up_rate()->rate();
  });
  CMD2_PEER("p.up_total", [](const auto& peer, const auto&) {
    return peer->up_rate()->total();
  });
  CMD2_PEER("p.down_rate", [](const auto& peer, const auto&) {
    return peer->down_rate()->rate();
  });
  CMD2_PEER("p.down_total", [](const auto& peer, const auto&) {
    return peer->down_rate()->total();
  });
  CMD2_PEER("p.peer_rate", [](const auto& peer, const auto&) {
    return peer->peer_rate()->rate();
  });
  CMD2_PEER("p.peer_total", [](const auto& peer, const auto&) {
    return peer->peer_rate()->total();
  });

  CMD2_PEER("p.snubbed",
            [](const auto& peer, const auto&) { return peer->is_snubbed(); });
  CMD2_PEER_VALUE_V("p.snubbed.set", [](const auto& peer, const auto& v) {
    return peer->set_snubbed(v);
  });
  CMD2_PEER("p.banned",
            [](const auto& peer, const auto&) { return peer->is_banned(); });
  CMD2_PEER_VALUE_V("p.banned.set", [](const auto& peer, const auto& v) {
    return peer->set_banned(v);
  });

  CMD2_PEER_V("p.disconnect", [](const auto& peer, const auto&) {
    return peer->disconnect(0);
  });
  CMD2_PEER_V("p.disconnect_delayed", [](const auto& peer, const auto&) {
    return peer->disconnect(torrent::ConnectionList::disconnect_delayed);
  });
}
