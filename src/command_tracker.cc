// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#include <cstdio>
#include <torrent/dht_manager.h>
#include <torrent/tracker.h>
#include <torrent/utils/address_info.h>
#include <torrent/utils/error_number.h>
#include <torrent/utils/log.h>

#include "core/download.h"
#include "core/manager.h"

#include "command_helpers.h"
#include "control.h"
#include "core/dht_manager.h"
#include "globals.h"

void
tracker_set_enabled(torrent::Tracker* tracker, bool state) {
  if (state)
    tracker->enable();
  else
    tracker->disable();
}

struct call_add_node_t {
  call_add_node_t(int port)
    : m_port(port) {}

  void operator()(const sockaddr* sa, int) {
    if (sa == NULL) {
      lt_log_print(torrent::LOG_DHT_WARN, "Could not resolve host.");
    } else {
      torrent::dht_manager()->add_node(sa, m_port);
    }
  }

  int m_port;
};

torrent::Object
apply_dht_add_node(const std::string& arg) {
  if (!torrent::dht_manager()->is_valid())
    throw torrent::input_error("DHT not enabled.");

  int  port, ret;
  char dummy;
  char host[1024];

  ret = std::sscanf(arg.c_str(), "%1023[^:]:%i%c", host, &port, &dummy);

  if (ret == 1)
    port = 6881;
  else if (ret != 2)
    throw torrent::input_error("Could not parse host.");

  if (port < 1 || port > 65535)
    throw torrent::input_error("Invalid port number.");

  torrent::connection_manager()->resolver()(
    host,
    (int)torrent::utils::socket_address::pf_inet,
    SOCK_DGRAM,
    call_add_node_t(port));
  return torrent::Object();
}

torrent::Object
apply_enable_trackers(int64_t arg) {
  for (core::Manager::DListItr itr  = control->core()->download_list()->begin(),
                               last = control->core()->download_list()->end();
       itr != last;
       ++itr) {
    std::for_each((*itr)->tracker_list()->begin(),
                  (*itr)->tracker_list()->end(),
                  arg ? std::mem_fun(&torrent::Tracker::enable)
                      : std::mem_fun(&torrent::Tracker::disable));

    if (arg && !rpc::call_command_value("trackers.use_udp"))
      (*itr)->enable_udp_trackers(false);
  }

  return torrent::Object();
}

void
initialize_command_tracker() {
  CMD2_TRACKER("t.is_open",
               std::bind(&torrent::Tracker::is_busy, std::placeholders::_1));
  CMD2_TRACKER("t.is_enabled",
               std::bind(&torrent::Tracker::is_enabled, std::placeholders::_1));
  CMD2_TRACKER("t.is_usable",
               std::bind(&torrent::Tracker::is_usable, std::placeholders::_1));
  CMD2_TRACKER("t.is_busy",
               std::bind(&torrent::Tracker::is_busy, std::placeholders::_1));
  CMD2_TRACKER(
    "t.is_extra_tracker",
    std::bind(&torrent::Tracker::is_extra_tracker, std::placeholders::_1));
  CMD2_TRACKER("t.can_scrape",
               std::bind(&torrent::Tracker::can_scrape, std::placeholders::_1));

  CMD2_TRACKER_V("t.enable",
                 std::bind(&torrent::Tracker::enable, std::placeholders::_1));
  CMD2_TRACKER_V("t.disable",
                 std::bind(&torrent::Tracker::disable, std::placeholders::_1));

  CMD2_TRACKER_VALUE_V("t.is_enabled.set",
                       std::bind(&tracker_set_enabled,
                                 std::placeholders::_1,
                                 std::placeholders::_2));

  CMD2_TRACKER("t.url",
               std::bind(&torrent::Tracker::url, std::placeholders::_1));
  CMD2_TRACKER("t.group",
               std::bind(&torrent::Tracker::group, std::placeholders::_1));
  CMD2_TRACKER("t.type",
               std::bind(&torrent::Tracker::type, std::placeholders::_1));
  CMD2_TRACKER("t.id",
               std::bind(&torrent::Tracker::tracker_id, std::placeholders::_1));

  CMD2_TRACKER(
    "t.latest_event",
    std::bind(&torrent::Tracker::latest_event, std::placeholders::_1));
  CMD2_TRACKER(
    "t.latest_new_peers",
    std::bind(&torrent::Tracker::latest_new_peers, std::placeholders::_1));
  CMD2_TRACKER(
    "t.latest_sum_peers",
    std::bind(&torrent::Tracker::latest_sum_peers, std::placeholders::_1));

  // Time since last connection, connection attempt.

  CMD2_TRACKER(
    "t.normal_interval",
    std::bind(&torrent::Tracker::normal_interval, std::placeholders::_1));
  CMD2_TRACKER(
    "t.min_interval",
    std::bind(&torrent::Tracker::min_interval, std::placeholders::_1));

  CMD2_TRACKER(
    "t.activity_time_next",
    std::bind(&torrent::Tracker::activity_time_next, std::placeholders::_1));
  CMD2_TRACKER(
    "t.activity_time_last",
    std::bind(&torrent::Tracker::activity_time_last, std::placeholders::_1));

  CMD2_TRACKER(
    "t.success_time_next",
    std::bind(&torrent::Tracker::success_time_next, std::placeholders::_1));
  CMD2_TRACKER(
    "t.success_time_last",
    std::bind(&torrent::Tracker::success_time_last, std::placeholders::_1));
  CMD2_TRACKER(
    "t.success_counter",
    std::bind(&torrent::Tracker::success_counter, std::placeholders::_1));

  CMD2_TRACKER(
    "t.failed_time_next",
    std::bind(&torrent::Tracker::failed_time_next, std::placeholders::_1));
  CMD2_TRACKER(
    "t.failed_time_last",
    std::bind(&torrent::Tracker::failed_time_last, std::placeholders::_1));
  CMD2_TRACKER(
    "t.failed_counter",
    std::bind(&torrent::Tracker::failed_counter, std::placeholders::_1));

  CMD2_TRACKER(
    "t.scrape_time_last",
    std::bind(&torrent::Tracker::scrape_time_last, std::placeholders::_1));
  CMD2_TRACKER(
    "t.scrape_counter",
    std::bind(&torrent::Tracker::scrape_counter, std::placeholders::_1));

  CMD2_TRACKER(
    "t.scrape_complete",
    std::bind(&torrent::Tracker::scrape_complete, std::placeholders::_1));
  CMD2_TRACKER(
    "t.scrape_incomplete",
    std::bind(&torrent::Tracker::scrape_incomplete, std::placeholders::_1));
  CMD2_TRACKER(
    "t.scrape_downloaded",
    std::bind(&torrent::Tracker::scrape_downloaded, std::placeholders::_1));

  CMD2_ANY_VALUE("trackers.enable",
                 std::bind(&apply_enable_trackers, int64_t(1)));
  CMD2_ANY_VALUE("trackers.disable",
                 std::bind(&apply_enable_trackers, int64_t(0)));
  CMD2_VAR_VALUE("trackers.numwant", -1);
  CMD2_VAR_BOOL("trackers.use_udp", true);

  CMD2_ANY_STRING_V("dht.mode.set",
                    std::bind(&core::DhtManager::set_mode,
                              control->dht_manager(),
                              std::placeholders::_2));
  CMD2_VAR_VALUE("dht.port", int64_t(6881));
  CMD2_ANY_STRING("dht.add_node",
                  std::bind(&apply_dht_add_node, std::placeholders::_2));
  CMD2_ANY(
    "dht.statistics",
    std::bind(&core::DhtManager::dht_statistics, control->dht_manager()));
  CMD2_ANY("dht.throttle.name",
           std::bind(&core::DhtManager::throttle_name, control->dht_manager()));
  CMD2_ANY_STRING_V("dht.throttle.name.set",
                    std::bind(&core::DhtManager::set_throttle_name,
                              control->dht_manager(),
                              std::placeholders::_2));
}
