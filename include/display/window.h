// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_WINDOW_BASE_H
#define RTORRENT_WINDOW_BASE_H

#include <functional>

#include <torrent/utils/timer.h>

#include "display/canvas.h"
#include "globals.h"

namespace display {

class Canvas;
class Manager;

class Window {
public:
  typedef uint32_t extent_type;

  typedef std::function<void()>                               Slot;
  typedef std::function<void(Window*)>                        SlotWindow;
  typedef std::function<void(Window*, torrent::utils::timer)> SlotTimer;

  static const int flag_active    = (1 << 0);
  static const int flag_offscreen = (1 << 1);
  static const int flag_focused   = (1 << 2);
  static const int flag_left      = (1 << 3);
  static const int flag_bottom    = (1 << 4);

  static const extent_type extent_static = extent_type();
  static const extent_type extent_full   = ~extent_type();

  Window(Canvas*     canvas,
         int         flags,
         extent_type minWidth,
         extent_type minHeight,
         extent_type maxWidth,
         extent_type maxHeight);

  virtual ~Window();

  bool is_active() const {
    return m_flags & flag_active;
  }
  void set_active(bool state);

  bool is_offscreen() const {
    return m_flags & flag_offscreen;
  }
  void set_offscreen(bool state) {
    if (state)
      m_flags |= flag_offscreen;
    else
      m_flags &= ~flag_offscreen;
  }

  bool is_focused() const {
    return m_flags & flag_focused;
  }
  void set_focused(bool state) {
    if (state)
      m_flags |= flag_focused;
    else
      m_flags &= ~flag_focused;
  }

  bool is_left() const {
    return m_flags & flag_left;
  }
  void set_left(bool state) {
    if (state)
      m_flags |= flag_left;
    else
      m_flags &= ~flag_left;
  }

  bool is_bottom() const {
    return m_flags & flag_bottom;
  }
  void set_bottom(bool state) {
    if (state)
      m_flags |= flag_bottom;
    else
      m_flags &= ~flag_bottom;
  }

  bool is_width_dynamic() const {
    return m_maxWidth > m_minWidth;
  }
  bool is_height_dynamic() const {
    return m_maxHeight > m_minHeight;
  }

  // Do not call mark_dirty() from withing redraw() as it may cause
  // infinite looping in the display scheduler.
  bool is_dirty() {
    return m_taskUpdate.is_queued();
  }
  void mark_dirty() {
    if (!is_active())
      return;
    m_slotSchedule(this, cachedTime);
  }

  extent_type min_width() const {
    return m_minWidth;
  }
  extent_type min_height() const {
    return m_minHeight;
  }

  extent_type max_width() const {
    return std::max(m_maxWidth, m_minWidth);
  }
  extent_type max_height() const {
    return std::max(m_maxHeight, m_minHeight);
  }

  extent_type width() const {
    return m_canvas->width();
  }
  extent_type height() const {
    return m_canvas->height();
  }

  void refresh() {
    m_canvas->refresh();
  }
  void resize(int x, int y, int w, int h);

  virtual void redraw() = 0;

  torrent::utils::priority_item* task_update() {
    return &m_taskUpdate;
  }

  // Slot for adjust and refresh.
  static void slot_schedule(SlotTimer s) {
    m_slotSchedule = s;
  }
  static void slot_unschedule(SlotWindow s) {
    m_slotUnschedule = s;
  }
  static void slot_adjust(Slot s) {
    m_slotAdjust = s;
  }

protected:
  Window(const Window&);
  void operator=(const Window&);

  static SlotTimer  m_slotSchedule;
  static SlotWindow m_slotUnschedule;
  static Slot       m_slotAdjust;

  Canvas* m_canvas;

  int m_flags;

  extent_type m_minWidth;
  extent_type m_minHeight;

  extent_type m_maxWidth;
  extent_type m_maxHeight;

  torrent::utils::priority_item m_taskUpdate;
};

}

#endif
