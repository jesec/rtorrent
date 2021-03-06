// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#include <cmath>
#include <stdexcept>
#include <torrent/bitfield.h>
#include <torrent/data/block.h>
#include <torrent/data/block_list.h>
#include <torrent/data/transfer_list.h>
#include <torrent/utils/string_manip.h>

#include "core/download.h"

#include "display/window_download_chunks_seen.h"

namespace display {

WindowDownloadChunksSeen::WindowDownloadChunksSeen(core::Download* d,
                                                   unsigned int*   focus)
  : Window(new Canvas, 0, 0, 0, extent_full, extent_full)
  , m_download(d)
  , m_focus(focus) {}

void
WindowDownloadChunksSeen::redraw() {
  // TODO: Make this depend on tracker signal.
  m_slotSchedule(
    this,
    (cachedTime + torrent::utils::timer::from_seconds(10)).round_seconds());
  m_canvas->erase();

  const auto height = m_canvas->height();
  const auto width  = m_canvas->width();
  if (height < 3 || width < 18) {
    return;
  }

  m_canvas->print(2,
                  0,
                  "Chunks seen: [C/A/D %i/%i/%.2f]",
                  (int)m_download->download()->peers_complete() +
                    m_download->download()->file_list()->is_done(),
                  (int)m_download->download()->peers_accounted(),
                  std::floor(m_download->distributed_copies() * 100.0f) /
                    100.0f);

  const uint8_t* seen = m_download->download()->chunks_seen();

  if (seen == nullptr ||
      m_download->download()->file_list()->bitfield()->empty()) {
    m_canvas->print(2, 2, "Not available.");
    return;
  }

  if (!m_download->is_done()) {
    m_canvas->print(36, 0, "X downloaded    missing    queued    downloading");
    m_canvas->print_char(50, 0, 'X' | A_BOLD);
    m_canvas->print_char(61, 0, 'X' | A_BOLD | A_UNDERLINE);
    m_canvas->print_char(71, 0, 'X' | A_REVERSE);
  }

  *m_focus = std::min(*m_focus, max_focus());

  const uint8_t* chunk = seen + *m_focus * chunks_per_row();
  const uint8_t* last =
    seen + m_download->download()->file_list()->size_chunks();

  const torrent::Bitfield* bitfield =
    m_download->download()->file_list()->bitfield();
  const torrent::TransferList* transfers =
    m_download->download()->transfer_list();
  std::vector<torrent::BlockList*> transferChunks(transfers->size(), nullptr);

  std::copy(transfers->begin(), transfers->end(), transferChunks.begin());
  std::sort(transferChunks.begin(),
            transferChunks.end(),
            [](torrent::BlockList* l1, torrent::BlockList* l2) {
              return l1->index() < l2->index();
            });

  std::vector<torrent::BlockList*>::const_iterator itrTransfer =
    transferChunks.begin();

  while (itrTransfer != transferChunks.end() &&
         (uint32_t)(chunk - seen) > (*itrTransfer)->index())
    itrTransfer++;

  for (unsigned int y = 1; y < height && chunk < last; ++y) {
    m_canvas->print(0, y, "%5u ", (int)(chunk - seen));

    while (chunk < last) {
      chtype attr;

      if (bitfield->get(chunk - seen)) {
        attr = A_NORMAL;
      } else if (itrTransfer != transferChunks.end() &&
                 (uint32_t)(chunk - seen) == (*itrTransfer)->index()) {
        if (std::find_if((*itrTransfer)->begin(),
                         (*itrTransfer)->end(),
                         [](torrent::Block& b) {
                           return b.is_transfering();
                         }) != (*itrTransfer)->end())
          attr = A_REVERSE;
        else
          attr = A_BOLD | A_UNDERLINE;
        itrTransfer++;
      } else {
        attr = A_BOLD;
      }

      m_canvas->print_char(attr | torrent::utils::value_to_hexchar<0>(
                                    std::min<uint8_t>(*chunk, 0xF)));
      chunk++;

      if ((chunk - seen) % 10 == 0) {
        if (m_canvas->get_x() + 12 > width)
          break;

        m_canvas->print_char(' ');
      }
    }
  }
}

unsigned int
WindowDownloadChunksSeen::rows() const {
  if (m_canvas->width() < 18)
    return 0;

  return (m_download->download()->file_list()->size_chunks() +
          chunks_per_row() - 1) /
         chunks_per_row();
}

}
