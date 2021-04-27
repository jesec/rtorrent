// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

// The DownloadFactory class assures that loading torrents can be done
// anywhere in the code by queueing the task. The user may change
// settings while, or even after, the torrent is loading.

#ifndef RTORRENT_CORE_DOWNLOAD_FACTORY_H
#define RTORRENT_CORE_DOWNLOAD_FACTORY_H

#include <functional>
#include <iosfwd>

#include <torrent/object.h>
#include <torrent/utils/priority_queue_default.h>

#include "core/http_queue.h"

namespace core {

class Manager;

class DownloadFactory {
public:
  using slot_void         = std::function<void()>;
  using command_list_type = std::vector<std::string>;

  // Do not destroy this object while it is in a HttpQueue.
  DownloadFactory(Manager* m);
  ~DownloadFactory();

  // Calling of receive_load() is delayed so you can change whatever
  // you want without fear of the slots being triggered as you call
  // load() or commit().
  void load(const std::string& uri);
  void load_raw_data(const std::string& input);
  void commit();

  command_list_type& commands() {
    return m_commands;
  }
  torrent::Object::string_type& result() {
    return m_result;
  }
  torrent::Object::map_type& variables() {
    return m_variables;
  }

  bool get_session() const {
    return m_session;
  }
  void set_session(bool v) {
    m_session = v;
  }

  bool get_start() const {
    return m_start;
  }
  void set_start(bool v) {
    m_start = v;
  }

  bool print_log() const {
    return m_printLog;
  }
  void set_print_log(bool v) {
    m_printLog = v;
  }

  bool immediate() const {
    return m_immediate;
  }
  void set_immediate(bool v) {
    m_immediate = v;
  }

  void slot_finished(slot_void s) {
    m_slot_finished = s;
  }

private:
  void receive_load();
  void receive_loaded();
  void receive_commit();
  void receive_success();
  void receive_failed(const std::string& msg);

  void log_created(Download* download, torrent::Object* rtorrent);

  void initialize_rtorrent(Download* download, torrent::Object* rtorrent);

  Manager*         m_manager;
  std::iostream*   m_stream{ nullptr };
  torrent::Object* m_object{ nullptr };

  bool m_commited{ false };
  bool m_loaded{ false };

  std::string m_uri;
  std::string m_result;
  bool        m_session{ false };
  bool        m_start{ false };
  bool        m_printLog{ true };
  bool        m_immediate{ false };
  bool        m_isFile{ false };

  command_list_type         m_commands;
  torrent::Object::map_type m_variables;

  slot_void                     m_slot_finished;
  torrent::utils::priority_item m_taskLoad;
  torrent::utils::priority_item m_taskCommit;
};

bool
is_data_uri(const std::string& uri);
bool
is_magnet_uri(const std::string& uri);
bool
is_network_uri(const std::string& uri);

}

#endif
