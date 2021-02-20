// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_DISPLAY_FILE_LIST_H
#define RTORRENT_DISPLAY_FILE_LIST_H

#include "display/window.h"

namespace ui {
class ElementFileList;
}

namespace torrent {
class File;
class FileListIterator;
class file_list_collapsed_iterator;
}

namespace display {

class WindowFileList : public Window {
public:
  using iterator           = torrent::FileListIterator;
  using collapsed_iterator = torrent::file_list_collapsed_iterator;

  WindowFileList(const ui::ElementFileList* element);

  void redraw() override;

private:
  int done_percentage(torrent::File* e);

  const ui::ElementFileList* m_element;
};

}

#endif
