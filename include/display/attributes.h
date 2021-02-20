#ifndef RTORRENT_DISPLAY_ATTRIBUTES_H
#define RTORRENT_DISPLAY_ATTRIBUTES_H

#include <string>
#include <vector>

#if __has_include(<ncursesw/curses.h>)
#include <ncursesw/curses.h>
#elif __has_include(<ncursesw.h>)
#include <ncursesw.h>
#elif __has_include(<ncurses/curses.h>)
#include <ncurses/curses.h>
#elif __has_include(<ncurses.h>)
#include <ncurses.h>
#elif __has_include(<curses.h>)
#include <curses.h>
#else
#error "SysV or X/Open-compatible Curses header file required"
#endif

// Let us hail the creators of curses for being idiots. The only
// clever move they made was in the naming.
#undef timeout
#undef move

namespace display {

class Attributes {
public:
  static constexpr int a_invalid = ~int();
  static constexpr int a_normal  = A_NORMAL;
  static constexpr int a_bold    = A_BOLD;
  static constexpr int a_reverse = A_REVERSE;

  static constexpr int color_invalid = ~int();
  static constexpr int color_default = 0;

  Attributes(const char* pos, int attr, int col)
    : m_position(pos)
    , m_attributes(attr)
    , m_colors(col) {}
  Attributes(const char* pos, const Attributes& old)
    : m_position(pos)
    , m_attributes(old.m_attributes)
    , m_colors(old.m_colors) {}

  const char* position() const {
    return m_position;
  }
  void set_position(const char* pos) {
    m_position = pos;
  }

  int attributes() const {
    return m_attributes;
  }
  void set_attributes(int attr) {
    m_attributes = attr;
  }

  int colors() const {
    return m_colors;
  }
  void set_colors(int col) {
    m_colors = col;
  }

private:
  const char* m_position;
  int         m_attributes;
  int         m_colors;
};

}

#endif
