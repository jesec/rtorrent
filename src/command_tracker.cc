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

std::pair<char*, int>
parse_host_port(const std::string& arg) {
  const auto& delimPos = arg.find_first_of(':');

  const auto& host = arg.substr(0, delimPos);
  if (host.size() > 1023) {
    throw torrent::input_error("Could not parse host.");
  }

  int port = 6881;
  if (delimPos != std::string::npos) {
    try {
      port = std::stoi(arg.substr(delimPos + 1));
    } catch (const std::logic_error&) {
      throw torrent::input_error("Invalid port number.");
    }
  }

  if (port < 1 || port > 65535) {
    throw torrent::input_error("Invalid port number.");
  }

  char* host_raw = new char[1024];
  std::strcpy(host_raw, host.c_str());

  return std::make_pair(host_raw, port);
}

torrent::Object
apply_dht_add_node(const std::string& arg) {
  if (!torrent::dht_manager()->is_valid()) {
    throw torrent::input_error("DHT not enabled.");
  }

  const auto& [host, port] = parse_host_port(arg);

  torrent::connection_manager()->resolver()(
    host,
    (int)torrent::utils::socket_address::pf_inet,
    SOCK_DGRAM,
    [&host = host, port = port](const sockaddr* sa, int) {
      if (sa == nullptr) {
        lt_log_print(torrent::LOG_DHT_WARN, "Could not resolve host.");
      } else {
        torrent::dht_manager()->add_node(sa, port);
      }
      delete[] host;
    });

  return torrent::Object();
}

torrent::Object
apply_dht_add_bootstrap(const std::string& arg) {
  const auto& [host, port] = parse_host_port(arg);

  control->dht_manager()->add_bootstrap(std::string(host), port);

  delete[] host;

  return torrent::Object();
}

torrent::Object
apply_enable_trackers(int64_t arg) {
  for (const auto& download : *control->core()->download_list()) {
    if (arg) {
      for (const auto& tracker : *download->tracker_list()) {
        tracker->enable();
      }
    } else {
      for (const auto& tracker : *download->tracker_list()) {
        tracker->disable();
      }
    }

    if (arg && !rpc::call_command_value("trackers.use_udp")) {
      download->enable_udp_trackers(false);
    }
  }

  return torrent::Object();
}

void
initialize_command_tracker() {
  CMD2_TRACKER("t.is_open", [](const auto& tracker, const auto&) {
    return tracker->is_busy();
  });
  CMD2_TRACKER("t.is_enabled", [](const auto& tracker, const auto&) {
    return tracker->is_enabled();
  });
  CMD2_TRACKER("t.is_usable", [](const auto& tracker, const auto&) {
    return tracker->is_usable();
  });
  CMD2_TRACKER("t.is_busy", [](const auto& tracker, const auto&) {
    return tracker->is_busy();
  });
  CMD2_TRACKER("t.is_extra_tracker", [](const auto& tracker, const auto&) {
    return tracker->is_extra_tracker();
  });
  CMD2_TRACKER("t.can_scrape", [](const auto& tracker, const auto&) {
    return tracker->can_scrape();
  });

  CMD2_TRACKER_V("t.enable", [](const auto& tracker, const auto&) {
    return tracker->enable();
  });
  CMD2_TRACKER_V("t.disable", [](const auto& tracker, const auto&) {
    return tracker->disable();
  });

  CMD2_TRACKER_VALUE_V("t.is_enabled.set",
                       [](const auto& tracker, const auto& state) {
                         return tracker_set_enabled(tracker, state);
                       });

  CMD2_TRACKER("t.url",
               [](const auto& tracker, const auto&) { return tracker->url(); });
  CMD2_TRACKER("t.group", [](const auto& tracker, const auto&) {
    return tracker->group();
  });
  CMD2_TRACKER(
    "t.type", [](const auto& tracker, const auto&) { return tracker->type(); });
  CMD2_TRACKER("t.id", [](const auto& tracker, const auto&) {
    return tracker->tracker_id();
  });

  CMD2_TRACKER("t.latest_event", [](const auto& tracker, const auto&) {
    return tracker->latest_event();
  });
  CMD2_TRACKER("t.latest_new_peers", [](const auto& tracker, const auto&) {
    return tracker->latest_new_peers();
  });
  CMD2_TRACKER("t.latest_sum_peers", [](const auto& tracker, const auto&) {
    return tracker->latest_sum_peers();
  });

  // Time since last connection, connection attempt.

  CMD2_TRACKER("t.normal_interval", [](const auto& tracker, const auto&) {
    return tracker->normal_interval();
  });
  CMD2_TRACKER("t.min_interval", [](const auto& tracker, const auto&) {
    return tracker->min_interval();
  });

  CMD2_TRACKER("t.activity_time_next", [](const auto& tracker, const auto&) {
    return tracker->activity_time_next();
  });
  CMD2_TRACKER("t.activity_time_last", [](const auto& tracker, const auto&) {
    return tracker->activity_time_last();
  });

  CMD2_TRACKER("t.success_time_next", [](const auto& tracker, const auto&) {
    return tracker->success_time_next();
  });
  CMD2_TRACKER("t.success_time_last", [](const auto& tracker, const auto&) {
    return tracker->success_time_last();
  });
  CMD2_TRACKER("t.success_counter", [](const auto& tracker, const auto&) {
    return tracker->success_counter();
  });

  CMD2_TRACKER("t.failed_time_next", [](const auto& tracker, const auto&) {
    return tracker->failed_time_next();
  });
  CMD2_TRACKER("t.failed_time_last", [](const auto& tracker, const auto&) {
    return tracker->failed_time_last();
  });
  CMD2_TRACKER("t.failed_counter", [](const auto& tracker, const auto&) {
    return tracker->failed_counter();
  });

  CMD2_TRACKER("t.scrape_time_last", [](const auto& tracker, const auto&) {
    return tracker->scrape_time_last();
  });
  CMD2_TRACKER("t.scrape_counter", [](const auto& tracker, const auto&) {
    return tracker->scrape_counter();
  });

  CMD2_TRACKER("t.scrape_complete", [](const auto& tracker, const auto&) {
    return tracker->scrape_complete();
  });
  CMD2_TRACKER("t.scrape_incomplete", [](const auto& tracker, const auto&) {
    return tracker->scrape_incomplete();
  });
  CMD2_TRACKER("t.scrape_downloaded", [](const auto& tracker, const auto&) {
    return tracker->scrape_downloaded();
  });

  CMD2_ANY_VALUE("trackers.enable", [](const auto&, const auto&) {
    return apply_enable_trackers(int64_t(1));
  });
  CMD2_ANY_VALUE("trackers.disable", [](const auto&, const auto&) {
    return apply_enable_trackers(int64_t(0));
  });
  CMD2_VAR_VALUE("trackers.numwant", -1);
  CMD2_VAR_BOOL("trackers.use_udp", true);

  CMD2_ANY_STRING_V("dht.mode.set", [](const auto&, const auto& arg) {
    return control->dht_manager()->set_mode(arg);
  });
  CMD2_VAR_VALUE("dht.port", int64_t(6881));
  CMD2_ANY_STRING("dht.add_bootstrap", [](const auto&, const auto& arg) {
    return apply_dht_add_bootstrap(arg);
  });
  CMD2_ANY_STRING("dht.add_node", [](const auto&, const auto& arg) {
    return apply_dht_add_node(arg);
  });
  CMD2_ANY("dht.statistics", [](const auto&, const auto&) {
    return control->dht_manager()->dht_statistics();
  });
  CMD2_ANY("dht.throttle.name", [](const auto&, const auto&) {
    return control->dht_manager()->throttle_name();
  });
  CMD2_ANY_STRING_V(
    "dht.throttle.name.set", [](const auto&, const auto& throttleName) {
      return control->dht_manager()->set_throttle_name(throttleName);
    });
}
