// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_UI_DOWNLOAD_LIST_H
#define RTORRENT_UI_DOWNLOAD_LIST_H

#include "display/manager.h"
#include "globals.h"
#include "ui/element_base.h"

class Control;

namespace core {
class Download;
class View;
}

namespace input {
class Bindings;
}

namespace display {
class Frame;
class WindowDownloadList;
class WindowHttpQueue;
class WindowInput;
class WindowLog;
class WindowLogComplete;
}

namespace ui {

class Download;

class DownloadList : public ElementBase {
public:
  using WList        = display::WindowDownloadList;
  using WLog         = display::WindowLog;
  using WLogComplete = display::WindowLogComplete;

  using slot_string = std::function<void(const std::string&)>;

  using Display = enum {
    DISPLAY_DOWNLOAD,
    DISPLAY_DOWNLOAD_LIST,
    DISPLAY_LOG,
    DISPLAY_STRING_LIST,
    DISPLAY_MAX_SIZE
  };

  using Input = enum {
    INPUT_NONE,
    INPUT_LOAD_DEFAULT,
    INPUT_LOAD_MODIFIED,
    INPUT_CHANGE_DIRECTORY,
    INPUT_COMMAND,
    INPUT_FILTER,
    INPUT_EOI
  };

  DownloadList();
  ~DownloadList() override;

  void activate(display::Frame* frame, bool focus = true) override;
  void disable() override;

  void activate_display(Display d);

  core::View* current_view();
  void        set_current_view(const std::string& name);

  void slot_open_uri(slot_string s) {
    m_slot_open_uri = s;
  }

  void unfocus_download(core::Download* d);

private:
  DownloadList(const DownloadList&);
  void operator=(const DownloadList&);

  void receive_view_input(Input type);
  void receive_exit_input(Input type);

  void setup_keys();
  void setup_input();

  Display m_state{ DISPLAY_MAX_SIZE };

  ElementBase* m_uiArray[DISPLAY_MAX_SIZE];
  WLog*        m_windowLog;

  slot_string m_slot_open_uri;
};

}

#endif
