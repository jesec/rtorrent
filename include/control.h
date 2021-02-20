// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_CONTROL_H
#define RTORRENT_CONTROL_H

#include <cinttypes>
#include <sys/types.h>

#include <torrent/torrent.h>
#include <torrent/utils/cacheline.h>
#include <torrent/utils/priority_queue_default.h>
#include <torrent/utils/timer.h>

namespace ui {
class Root;
}

namespace core {
class Manager;
class ViewManager;
class DhtManager;
}

namespace display {
class Manager;
}

namespace input {
class InputEvent;
class Manager;
}

namespace rpc {
class CommandScheduler;
class XmlRpc;
class object_storage;
}

namespace torrent {
class directory_events;
}

class Control {
public:
  Control();
  ~Control();

  bool is_shutdown_completed();
  bool is_shutdown_received() {
    return m_shutdownReceived;
  }
  bool is_shutdown_started() {
    return m_shutdownQuick;
  }

  void initialize();
  void cleanup();
  void cleanup_exception();

  void handle_shutdown();

  void receive_normal_shutdown() {
    m_shutdownReceived = true;
    __sync_synchronize();
  }
  void receive_quick_shutdown() {
    m_shutdownReceived = true;
    m_shutdownQuick    = true;
    __sync_synchronize();
  }

  core::Manager* core() {
    return m_core;
  }
  core::ViewManager* view_manager() {
    return m_viewManager;
  }
  core::DhtManager* dht_manager() {
    return m_dhtManager;
  }

  ui::Root* ui() {
    return m_ui;
  }
  display::Manager* display() {
    return m_display;
  }
  input::Manager* input() {
    return m_input;
  }
  input::InputEvent* input_stdin() {
    return m_inputStdin;
  }

  rpc::CommandScheduler* command_scheduler() {
    return m_commandScheduler;
  }
  rpc::object_storage* object_storage() {
    return m_objectStorage;
  }

  torrent::directory_events* directory_events() {
    return m_directory_events;
  }

  uint64_t tick() const {
    return m_tick;
  }
  void inc_tick() {
    m_tick++;
  }

  const std::string& working_directory() const {
    return m_workingDirectory;
  }
  void set_working_directory(const std::string& dir);

private:
  Control(const Control&);
  void operator=(const Control&);

  bool m_shutdownReceived lt_cacheline_aligned{ false };

  core::Manager*     m_core;
  core::ViewManager* m_viewManager;
  core::DhtManager*  m_dhtManager;

  ui::Root*          m_ui;
  display::Manager*  m_display;
  input::Manager*    m_input;
  input::InputEvent* m_inputStdin;

  bool m_shutdownQuick lt_cacheline_aligned{ false };

  rpc::CommandScheduler*     m_commandScheduler;
  rpc::object_storage*       m_objectStorage;
  torrent::directory_events* m_directory_events;

  uint64_t m_tick{ 0 };

  std::string m_workingDirectory;

  torrent::utils::priority_item m_taskShutdown;
};

#endif
