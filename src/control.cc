// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#include "config.h"

#include <sys/stat.h>
#include <torrent/connection_manager.h>
#include <torrent/utils/directory_events.h>
#include <unistd.h>

#include "core/dht_manager.h"
#include "core/download_store.h"
#include "core/http_queue.h"
#include "core/manager.h"
#include "core/view_manager.h"

#include "display/canvas.h"
#include "display/manager.h"
#include "display/window.h"
#include "input/input_event.h"
#include "input/manager.h"
#include "rpc/command_scheduler.h"
#include "rpc/object_storage.h"
#include "rpc/parse_commands.h"
#include "rpc/scgi.h"
#include "ui/root.h"
#include "utils/functional_fun.h"

#include "control.h"

Control::Control()
  : m_ui(new ui::Root())
  , m_display(new display::Manager())
  , m_input(new input::Manager())
  , m_inputStdin(new input::InputEvent(STDIN_FILENO))
  ,

  m_commandScheduler(new rpc::CommandScheduler())
  , m_objectStorage(new rpc::object_storage())
  , m_directory_events(new torrent::directory_events())
  ,

  m_tick(0)
  , m_shutdownReceived(false)
  , m_shutdownQuick(false) {

  m_core        = new core::Manager();
  m_viewManager = new core::ViewManager();
  m_dhtManager  = new core::DhtManager();

  m_inputStdin->slot_pressed(
    std::bind(&input::Manager::pressed, m_input, std::placeholders::_1));

  m_taskShutdown.slot() = std::bind(&Control::handle_shutdown, this);

  m_commandScheduler->set_slot_error_message(
    utils::mem_fn(m_core, &core::Manager::push_log_std));
}

Control::~Control() {
  delete m_inputStdin;
  delete m_input;

  delete m_viewManager;

  delete m_ui;
  delete m_display;
  delete m_core;
  delete m_dhtManager;

  delete m_directory_events;
  delete m_commandScheduler;
  delete m_objectStorage;
}

void
Control::initialize() {
  display::Canvas::initialize();
  display::Window::slot_schedule(
    torrent::utils::make_mem_fun(m_display, &display::Manager::schedule));
  display::Window::slot_unschedule(
    torrent::utils::make_mem_fun(m_display, &display::Manager::unschedule));
  display::Window::slot_adjust(
    torrent::utils::make_mem_fun(m_display, &display::Manager::adjust_layout));

  m_core->http_stack()->set_user_agent(USER_AGENT);

  m_core->initialize_second();
  m_core->listen_open();
  m_core->download_store()->enable(rpc::call_command_value("session.use_lock"));

  m_core->set_hashing_view(*m_viewManager->find_throw("hashing"));

  m_ui->init(this);

  if (!display::Canvas::daemon()) {
    m_inputStdin->insert(torrent::main_thread()->poll());
  }
}

void
Control::cleanup() {
  //  delete m_scgi; m_scgi = NULL;
  rpc::xmlrpc.cleanup();

  priority_queue_erase(&taskScheduler, &m_taskShutdown);

  if (!display::Canvas::daemon()) {
    m_inputStdin->remove(torrent::main_thread()->poll());
  }

  m_core->download_store()->disable();

  m_ui->cleanup();
  m_core->cleanup();

  display::Canvas::erase_std();
  display::Canvas::refresh_std();
  display::Canvas::do_update();
  display::Canvas::cleanup();
}

void
Control::cleanup_exception() {
  //  delete m_scgi; m_scgi = NULL;

  display::Canvas::cleanup();
}

bool
Control::is_shutdown_completed() {
  if (!m_shutdownQuick || worker_thread->is_active())
    return false;

  // Tracker requests can be disowned, so wait for these to
  // finish. The edge case of torrent http downloads may delay
  // shutdown.
  if (!core()->http_stack()->empty() || !core()->http_queue()->empty())
    return false;

  return torrent::is_inactive();
}

void
Control::handle_shutdown() {
  rpc::commands.call_catch("event.system.shutdown",
                           rpc::make_target(),
                           "shutdown",
                           "System shutdown event action failed: ");

  if (!m_shutdownQuick) {
    // Temporary hack:
    if (worker_thread->is_active())
      worker_thread->queue_item(&ThreadBase::stop_thread);

    torrent::connection_manager()->listen_close();
    m_directory_events->close();
    m_core->shutdown(false);

    if (!m_taskShutdown.is_queued())
      priority_queue_insert(&taskScheduler,
                            &m_taskShutdown,
                            cachedTime +
                              torrent::utils::timer::from_seconds(5));

  } else {
    // Temporary hack:
    if (worker_thread->is_active())
      worker_thread->queue_item(&ThreadBase::stop_thread);

    m_core->shutdown(true);
  }

  m_shutdownQuick    = true;
  m_shutdownReceived = false;
}
