// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#include <torrent/exceptions.h>
#include <torrent/tracker.h>
#include <torrent/tracker_controller.h>
#include <torrent/tracker_list.h>
#include <torrent/utils/algorithm.h>
#include <torrent/utils/string_manip.h>

#include "core/download.h"

#include "display/window_tracker_list.h"

namespace display {

WindowTrackerList::WindowTrackerList(core::Download* d, unsigned int* focus)
  : Window(new Canvas, 0, 0, 0, extent_full, extent_full)
  , m_download(d)
  , m_focus(focus) {}

void
WindowTrackerList::redraw() {
  // TODO: Make this depend on tracker signal.
  m_slotSchedule(
    this,
    (cachedTime + torrent::utils::timer::from_seconds(10)).round_seconds());
  m_canvas->erase();

  const auto height = m_canvas->height();
  const auto width  = m_canvas->width();
  if (height < 3 || width < 10) {
    return;
  }

  unsigned int                pos = 0;
  torrent::TrackerList*       tl  = m_download->tracker_list();
  torrent::TrackerController* tc  = m_download->tracker_controller();

  m_canvas->print(2,
                  pos,
                  "Trackers: [Key: %08x] [%s %s %s]",
                  tl->key(),
                  tc->is_requesting() ? "req" : "   ",
                  tc->is_promiscuous_mode() ? "prom" : "    ",
                  tc->is_failure_mode() ? "fail" : "    ");
  ++pos;

  if (tl->size() == 0 || *m_focus >= tl->size())
    return;

  using Range = std::pair<unsigned int, unsigned int>;

  Range range = torrent::utils::advance_bidirectional<unsigned int>(
    0, *m_focus, tl->size(), (height - 1) / 2);
  unsigned int group = tl->at(range.first)->group();

  while (range.first != range.second) {
    torrent::Tracker* tracker = tl->at(range.first);

    if (tracker->group() == group)
      m_canvas->print(0, pos, "%2i:", group++);

    m_canvas->print(4, pos++, "%s", tracker->url().c_str());

    if (pos < height) {
      const char* state;

      if (tracker->is_busy_not_scrape())
        state = "req ";
      else if (tracker->is_busy())
        state = "scr ";
      else
        state = "    ";

      m_canvas->print(
        0,
        pos++,
        "%s Id: %s Counters: %uf / %us (%u) %s S/L/D: %u/%u/%u (%u/%u)",
        state,
        torrent::utils::copy_escape_html(tracker->tracker_id()).c_str(),
        tracker->failed_counter(),
        tracker->success_counter(),
        tracker->scrape_counter(),
        tracker->is_usable()    ? " on"
        : tracker->is_enabled() ? "err"
                                : "off",
        tracker->scrape_complete(),
        tracker->scrape_incomplete(),
        tracker->scrape_downloaded(),
        tracker->latest_new_peers(),
        tracker->latest_sum_peers());
    }

    if (range.first == *m_focus) {
      m_canvas->set_attr(
        4, pos - 2, width, is_focused() ? A_REVERSE : A_BOLD, COLOR_PAIR(0));
      m_canvas->set_attr(
        4, pos - 1, width, is_focused() ? A_REVERSE : A_BOLD, COLOR_PAIR(0));
    }

    if (tracker->is_busy()) {
      m_canvas->set_attr(0, pos - 2, 4, A_REVERSE, COLOR_PAIR(0));
      m_canvas->set_attr(0, pos - 1, 4, A_REVERSE, COLOR_PAIR(0));
    }

    range.first++;

    // If we're at the end of the range, check if we can
    // show one more line for the following tracker.
    if (range.first == range.second && pos < height && range.first < tl->size())
      range.second++;
  }
}

}
