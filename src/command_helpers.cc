// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#include <torrent/exceptions.h>

#include "command_helpers.h"
#include "control.h"
#include "globals.h"

void
initialize_command_dynamic();
void
initialize_command_download();
void
initialize_command_events();
void
initialize_command_file();
void
initialize_command_ip();
void
initialize_command_peer();
void
initialize_command_local();
void
initialize_command_logging();
void
initialize_command_network();
void
initialize_command_groups();
void
initialize_command_throttle();
void
initialize_command_tracker();
void
initialize_command_scheduler();
void
initialize_command_ui();

void
initialize_commands() {
  initialize_command_dynamic();
  initialize_command_events();
  initialize_command_network();
  initialize_command_groups();
  initialize_command_local();
  initialize_command_logging();
  initialize_command_ui();
  initialize_command_download();
  initialize_command_file();
  initialize_command_ip();
  initialize_command_peer();
  initialize_command_throttle();
  initialize_command_tracker();
  initialize_command_scheduler();
}
