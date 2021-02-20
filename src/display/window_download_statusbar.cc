// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#include <torrent/data/transfer_list.h>
#include <torrent/peer/connection_list.h>
#include <torrent/peer/peer_list.h>
#include <torrent/rate.h>
#include <torrent/tracker_controller.h>
#include <torrent/tracker_list.h>

#include "core/download.h"
#include "display/canvas.h"
#include "display/utils.h"
#include "globals.h"

#include "display/window_download_statusbar.h"

namespace display {

WindowDownloadStatusbar::WindowDownloadStatusbar(core::Download* d)
  : Window(new Canvas, 0, 0, 3, extent_full, extent_static)
  , m_download(d) {}

void
WindowDownloadStatusbar::redraw() {
  m_slotSchedule(
    this,
    (cachedTime + torrent::utils::timer::from_seconds(1)).round_seconds());

  m_canvas->erase();

  const auto height = m_canvas->height();
  const auto width  = m_canvas->width();
  if (height < 3 || width < 18) {
    return;
  }

  char* buffer = static_cast<char*>(calloc(width, sizeof(char)));
  char* last   = buffer + width - 2;

  print_download_info_full(buffer, last, m_download);
  m_canvas->print(0, 0, "%s", buffer);

  snprintf(buffer,
           last - buffer,
           "Peers: %i(%i) Min/Max: %i/%i Slots: U:%i/%i D:%i/%i U/I/C/A: "
           "%i/%i/%i/%i Unchoked: %u/%u Failed: %i",
           (int)m_download->download()->connection_list()->size(),
           (int)m_download->download()->peer_list()->available_list_size(),
           (int)m_download->download()->connection_list()->min_size(),
           (int)m_download->download()->connection_list()->max_size(),
           (int)m_download->download()->uploads_min(),
           (int)m_download->download()->uploads_max(),
           (int)m_download->download()->downloads_min(),
           (int)m_download->download()->downloads_max(),
           (int)m_download->download()->peers_currently_unchoked(),
           (int)m_download->download()->peers_currently_interested(),
           (int)m_download->download()->peers_complete(),
           (int)m_download->download()->peers_accounted(),
           (int)m_download->info()->upload_unchoked(),
           (int)m_download->info()->download_unchoked(),
           (int)m_download->download()->transfer_list()->failed_count());

  m_canvas->print(0, 1, "%s", buffer);

  print_download_status(buffer, last, m_download);
  m_canvas->print(0,
                  2,
                  "[%c:%i] %s",
                  m_download->tracker_list()->has_active() ? 'C' : ' ',
                  (int)(m_download->download()
                          ->tracker_controller()
                          ->seconds_to_next_timeout()),
                  buffer);

  free(buffer);
}

}
