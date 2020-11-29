// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#include <algorithm>
#include <stdexcept>

#include "display/canvas.h"
#include "display/window.h"
#include "globals.h"

#include "display/manager.h"

namespace display {

Manager::Manager()
  : m_forceRedraw(false) {

  m_taskUpdate.slot() = std::bind(&Manager::receive_update, this);
}

Manager::~Manager() {
  priority_queue_erase(&taskScheduler, &m_taskUpdate);
}

void
Manager::force_redraw() {
  m_forceRedraw = true;
}

void
Manager::schedule(Window* w, torrent::utils::timer t) {
  torrent::utils::priority_queue_erase(&m_scheduler, w->task_update());
  torrent::utils::priority_queue_insert(&m_scheduler, w->task_update(), t);
  schedule_update(50000);
}

void
Manager::unschedule(Window* w) {
  torrent::utils::priority_queue_erase(&m_scheduler, w->task_update());
  schedule_update(50000);
}

void
Manager::adjust_layout() {
  Canvas::redraw_std();
  m_rootFrame.balance(
    0, 0, Canvas::get_screen_width(), Canvas::get_screen_height());

  schedule_update(0);
}

void
Manager::receive_update() {
  if (m_forceRedraw) {
    m_forceRedraw = false;

    display::Canvas::resize_term(display::Canvas::term_size());
    Canvas::redraw_std();

    adjust_layout();
    m_rootFrame.redraw();
  }

  Canvas::refresh_std();

  torrent::utils::priority_queue_perform(&m_scheduler, cachedTime);
  m_rootFrame.refresh();

  Canvas::do_update();

  m_timeLastUpdate = cachedTime;
  schedule_update(50000);
}

void
Manager::schedule_update(uint32_t minInterval) {
  if (m_scheduler.empty()) {
    torrent::utils::priority_queue_erase(&taskScheduler, &m_taskUpdate);
    return;
  }

  if (!m_taskUpdate.is_queued() ||
      m_taskUpdate.time() > m_scheduler.top()->time()) {
    torrent::utils::priority_queue_erase(&taskScheduler, &m_taskUpdate);
    torrent::utils::priority_queue_insert(
      &taskScheduler,
      &m_taskUpdate,
      std::max(m_scheduler.top()->time(), m_timeLastUpdate + minInterval));
  }
}

}
