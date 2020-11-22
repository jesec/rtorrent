// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#include "config.h"

#include <sys/ioctl.h>
#include <termios.h>
#include <torrent/exceptions.h>
#include <unistd.h>

#include "rpc/parse_commands.h"

#include "display/canvas.h"

namespace display {

bool Canvas::m_isInitialized = false;
bool Canvas::m_isDaemon      = false;

Canvas::Canvas(int x, int y, int width, int height) {
  if (!m_isDaemon) {
    m_window = newwin(height, width, y, x);

    if (m_window == NULL)
      throw torrent::internal_error("Could not allocate ncurses canvas.");
  }
}

void
Canvas::resize(int x, int y, int w, int h) {
  if (!m_isDaemon) {
    wresize(m_window, h, w);
    mvwin(m_window, y, x);
  }
}

void
Canvas::print_attributes(unsigned int           x,
                         unsigned int           y,
                         const char*            first,
                         const char*            last,
                         const attributes_list* attributes) {
  if (!m_isDaemon) {
    move(x, y);

    attr_t org_attr;
    short  org_pair;
    wattr_get(m_window, &org_attr, &org_pair, NULL);

    attributes_list::const_iterator attrItr = attributes->begin();
    wattr_set(m_window, Attributes::a_normal, Attributes::color_default, NULL);

    while (first != last) {
      const char* next = last;

      if (attrItr != attributes->end()) {
        next = attrItr->position();

        if (first >= next) {
          wattr_set(m_window, attrItr->attributes(), attrItr->colors(), NULL);
          ++attrItr;
        }
      }

      print("%.*s", next - first, first);
      first = next;
    }

    // Reset the color.
    wattr_set(m_window, org_attr, org_pair, NULL);
  }
}

void
Canvas::initialize() {
  if (m_isInitialized)
    return;

  m_isDaemon = rpc::call_command_value("system.daemon");

  m_isInitialized = true;

  if (!m_isDaemon) {
    initscr();
    raw();
    noecho();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    curs_set(0);
  }
}

void
Canvas::cleanup() {
  if (!m_isInitialized)
    return;

  m_isInitialized = false;

  if (!m_isDaemon) {
    noraw();
    endwin();
  }
}

std::pair<int, int>
Canvas::term_size() {
  struct winsize ws;

  if (!m_isDaemon) {
    if (ioctl(STDIN_FILENO, TIOCGWINSZ, &ws) == 0)
      return std::pair<int, int>(ws.ws_col, ws.ws_row);
  }
  return std::pair<int, int>(80, 24);
}

}
