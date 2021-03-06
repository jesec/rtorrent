// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#include <locale>
#include <stdio.h>
#include <torrent/data/file.h>
#include <torrent/data/file_list.h>
#include <torrent/data/file_list_iterator.h>
#include <torrent/path.h>

#include "core/download.h"
#include "ui/element_file_list.h"

#include "display/window_file_list.h"

namespace display {

// Don't really like the direction of the element dependency, but
// don't really feel like making a seperate class for containing the
// necessary information.
WindowFileList::WindowFileList(const ui::ElementFileList* element)
  : Window(new Canvas, 0, 0, 0, extent_full, extent_full)
  , m_element(element) {}

// Convert std::string to std::wstring of given width (in screen positions),
// taking into account that some characters may be occupying two screen
// positions.
std::wstring
wstring_width(const std::string& i_str, int width) {
  wchar_t* buf    = static_cast<wchar_t*>(calloc(width + 1, sizeof(wchar_t)));
  size_t   length = std::mbstowcs(buf, i_str.c_str(), width);

  // If not valid UTF-8 encoding, at least copy the printable characters.
  if (length == (size_t)-1) {
    wchar_t* out = buf;

    for (std::string::const_iterator itr = i_str.begin();
         out != buf + width && itr != i_str.end();
         ++itr)
      if (!std::isprint(*itr, std::locale::classic()))
        *out++ = '?';
      else
        *out++ = *itr;

    *out = 0;
  }

  int swidth = wcswidth(buf, width);

  // Limit to width if it's too wide already.
  if (swidth == -1 || swidth > width) {
    length = swidth = 0;

    while (buf[length]) {
      int next = ::wcwidth(buf[length]);

      // Unprintable character?
      if (next == -1) {
        buf[length] = '?';
        next        = 1;
      }

      if (swidth + next > width) {
        buf[length] = 0;
        break;
      }

      length++;
      swidth += next;
    }
  }

  // Pad with spaces to given width.
  while (swidth < width && length <= (unsigned int)width) {
    buf[length++] = ' ';
    swidth++;
  }

  buf[length] = 0;

  std::wstring result(buf);

  free(buf);

  return result;
}

void
WindowFileList::redraw() {
  m_slotSchedule(
    this,
    (cachedTime + torrent::utils::timer::from_seconds(10)).round_seconds());
  m_canvas->erase();

  torrent::FileList* fl = m_element->download()->download()->file_list();

  const auto height = m_canvas->height();
  const auto width  = m_canvas->width();
  if (fl->size_files() == 0 || height < 3 || width < 18) {
    return;
  }

  std::vector<iterator> entries(height - 1);

  unsigned int last = 0;

  for (iterator itr = m_element->selected(); last != height - 1;) {
    if (m_element->is_collapsed())
      itr.forward_current_depth();
    else
      ++itr;

    entries[last++] = itr;

    if (itr == iterator(fl->end()))
      break;
  }

  unsigned int first = height - 1;

  for (iterator itr = m_element->selected();
       first >= last || first > (height - 1) / 2;) {
    entries[--first] = itr;

    if (itr == iterator(fl->begin()))
      break;

    if (m_element->is_collapsed())
      itr.backward_current_depth();
    else
      --itr;
  }

  unsigned int pos           = 0;
  int          filenameWidth = width - 16;

  m_canvas->print(0, pos++, "Cmp Pri  Size   Filename");

  while (pos != height) {
    iterator itr = entries[first];

    if (itr == iterator(fl->end()))
      break;

    m_canvas->set_default_attributes(itr == m_element->selected()
                                       ? is_focused() ? A_REVERSE : A_BOLD
                                       : A_NORMAL);

    if (itr.is_empty()) {
      m_canvas->print(0, pos, "%*c%-*s", 16, ' ', filenameWidth, "EMPTY");

    } else if (itr.is_entering()) {
      m_canvas->print(0,
                      pos,
                      "%*c %ls",
                      16 + itr.depth(),
                      '\\',
                      itr.depth() < (*itr)->path()->size()
                        ? wstring_width((*itr)->path()->at(itr.depth()),
                                        filenameWidth - itr.depth() - 1)
                            .c_str()
                        : L"UNKNOWN");

    } else if (itr.is_leaving()) {
      m_canvas->print(0,
                      pos,
                      "%*c %-*s",
                      16 + (itr.depth() - 1),
                      '/',
                      filenameWidth - (itr.depth() - 1),
                      "");

    } else if (itr.is_file()) {
      torrent::File* e = *itr;

      const char* priority;

      switch (e->priority()) {
        case torrent::PRIORITY_OFF:
          priority = "off";
          break;
        case torrent::PRIORITY_NORMAL:
          priority = "   ";
          break;
        case torrent::PRIORITY_HIGH:
          priority = "hig";
          break;
        default:
          priority = "BUG";
          break;
      };

      m_canvas->print(0, pos, "%3d %s ", done_percentage(e), priority);

      int64_t val = e->size_bytes();

      if (val < (int64_t(1000) << 10))
        m_canvas->print(8, pos, "%5.1f K", (double)val / (int64_t(1) << 10));
      else if (val < (int64_t(1000) << 20))
        m_canvas->print(8, pos, "%5.1f M", (double)val / (int64_t(1) << 20));
      else if (val < (int64_t(1000) << 30))
        m_canvas->print(8, pos, "%5.1f G", (double)val / (int64_t(1) << 30));
      else
        m_canvas->print(8, pos, "%5.1f T", (double)val / (int64_t(1) << 40));

      m_canvas->print(15,
                      pos,
                      "%*c %ls",
                      1 + itr.depth(),
                      '|',
                      itr.depth() < (*itr)->path()->size()
                        ? wstring_width((*itr)->path()->at(itr.depth()),
                                        filenameWidth - itr.depth() - 1)
                            .c_str()
                        : L"UNKNOWN");

    } else {
      m_canvas->print(0, pos, "BORK BORK");
    }
    m_canvas->set_default_attributes(A_NORMAL);

    pos++;
    first = (first + 1) % (height - 1);
  }
}

int
WindowFileList::done_percentage(torrent::File* e) {
  int chunks = e->range().second - e->range().first;

  return chunks ? (e->completed_chunks() * 100) / chunks : 100;
}

}
