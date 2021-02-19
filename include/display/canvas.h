// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_DISPLAY_CANVAS_H
#define RTORRENT_DISPLAY_CANVAS_H

#include <string>
#include <vector>

#include "display/attributes.h"

namespace display {

class Canvas {
public:
  typedef std::vector<Attributes> attributes_list;

  Canvas(int x = 0, int y = 0, int width = 0, int height = 0);
  ~Canvas() {
    if (m_isInitialized) {
      delwin(m_window);
    }
  }

  void refresh() {
    if (m_isInitialized) {
      wnoutrefresh(m_window);
    }
  }
  static void refresh_std() {
    if (m_isInitialized) {
      wnoutrefresh(stdscr);
    }
  }
  void redraw() {
    if (m_isInitialized) {
      redrawwin(m_window);
    }
  }
  static void redraw_std() {
    if (m_isInitialized) {
      redrawwin(stdscr);
    }
  }

  void resize(int w, int h) {
    if (m_isInitialized) {
      wresize(m_window, h, w);
    }
  }
  void resize(int x, int y, int w, int h);

  static void resize_term(int x, int y) {
    if (m_isInitialized) {
      resizeterm(y, x);
    }
  }
  static void resize_term(std::pair<int, int> dim) {
    if (m_isInitialized) {
      resizeterm(dim.second, dim.first);
    }
  }

  unsigned int get_x() {
    if (m_isInitialized) {
      int                  x;
      [[maybe_unused]] int y;

      getyx(m_window, y, x);

      return x;
    } else {
      return 1;
    }
  }
  unsigned int get_y() {
    if (m_isInitialized) {
      [[maybe_unused]] int x;
      int                  y;

      getyx(m_window, y, x);

      return y;
    } else {
      return 1;
    }
  }

  unsigned int width() {
    if (m_isInitialized) {
      int                  x;
      [[maybe_unused]] int y;

      getmaxyx(m_window, y, x);

      return x;
    } else {
      return 80;
    }
  }
  unsigned int height() {
    if (m_isInitialized) {
      [[maybe_unused]] int x;
      int                  y;

      getmaxyx(m_window, y, x);

      return y;
    } else {
      return 24;
    }
  }

  void move(unsigned int x, unsigned int y) {
    if (m_isInitialized) {
      wmove(m_window, y, x);
    }
  }

  chtype get_background() {
    chtype bg = 0;
    if (m_isInitialized) {
      bg = getbkgd(m_window);
    }
    return bg;
  }
  void set_background(chtype c) {
    if (m_isInitialized) {
      return wbkgdset(m_window, c);
    }
  }

  void erase() {
    if (m_isInitialized) {
      werase(m_window);
    }
  }
  static void erase_std() {
    if (m_isInitialized) {
      werase(stdscr);
    }
  }

  void print_border(chtype ls,
                    chtype rs,
                    chtype ts,
                    chtype bs,
                    chtype tl,
                    chtype tr,
                    chtype bl,
                    chtype br) {
    if (m_isInitialized) {
      wborder(m_window, ls, rs, ts, bs, tl, tr, bl, br);
    }
  }

  // The format string is non-const, but that will not be a problem
  // since the string shall always be a C string choosen at
  // compiletime. Might cause extra copying of the string?

  void print(const char* str, ...);
  void print(unsigned int x, unsigned int y, const char* str, ...);

  void print_attributes(unsigned int           x,
                        unsigned int           y,
                        const char*            first,
                        const char*            last,
                        const attributes_list* attributes);

  void print_char(const chtype ch) {
    if (m_isInitialized) {
      waddch(m_window, ch);
    }
  }
  void print_char(unsigned int x, unsigned int y, const chtype ch) {
    if (m_isInitialized) {
      mvwaddch(m_window, y, x, ch);
    }
  }

  void set_attr(unsigned int x,
                unsigned int y,
                unsigned int n,
                int          attr,
                int          color) {
    if (m_isInitialized) {
      mvwchgat(m_window, y, x, n, attr, color, NULL);
    }
  }

  void set_default_attributes(int attr) {
    if (m_isInitialized) {
      (void)wattrset(m_window, attr);
    }
  }

  // Initialize stdscr.
  static void initialize();
  static void cleanup();

  static int get_screen_width() {
    if (m_isInitialized) {
      int                  x;
      [[maybe_unused]] int y;

      getmaxyx(stdscr, y, x);

      return x;
    } else {
      return 80;
    }
  }
  static int get_screen_height() {
    if (m_isInitialized) {
      [[maybe_unused]] int x;
      int                  y;

      getmaxyx(stdscr, y, x);

      return y;
    } else {
      return 24;
    }
  }

  static std::pair<int, int> term_size();

  static void do_update() {
    if (m_isInitialized) {
      doupdate();
    }
  }

  static bool isInitialized() {
    return m_isInitialized;
  }

private:
  Canvas(const Canvas&);
  void operator=(const Canvas&);

  static bool m_isInitialized;

  WINDOW* m_window;
};

inline void
Canvas::print(const char* str, ...) {
  va_list arglist;

  if (m_isInitialized) {
    va_start(arglist, str);
    vw_printw(m_window, const_cast<char*>(str), arglist);
    va_end(arglist);
  }
}

inline void
Canvas::print(unsigned int x, unsigned int y, const char* str, ...) {
  va_list arglist;

  if (m_isInitialized) {
    va_start(arglist, str);
    wmove(m_window, y, x);
    vw_printw(m_window, const_cast<char*>(str), arglist);
    va_end(arglist);
  }
}

}

#endif
