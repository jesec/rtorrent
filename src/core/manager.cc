// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#include <cstdio>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <glob.h>
#include <sstream>
#include <sys/select.h>

#include <torrent/connection_manager.h>
#include <torrent/error.h>
#include <torrent/exceptions.h>
#include <torrent/object.h>
#include <torrent/object_stream.h>
#include <torrent/throttle.h>
#include <torrent/tracker_list.h>
#include <torrent/utils/address_info.h>
#include <torrent/utils/error_number.h>
#include <torrent/utils/log.h>
#include <torrent/utils/path.h>
#include <torrent/utils/resume.h>
#include <torrent/utils/string_manip.h>
#include <unistd.h>

#include "rpc/parse_commands.h"
#include "utils/directory.h"
#include "utils/file_status_cache.h"

#include "control.h"
#include "core/curl_get.h"
#include "core/download.h"
#include "core/download_factory.h"
#include "core/download_store.h"
#include "core/http_queue.h"
#include "core/manager.h"
#include "core/poll_manager.h"
#include "core/view.h"
#include "globals.h"

namespace core {

constexpr static char padCharacter = '=';
static std::string
base64Decode(const std::string_view& input) {
  if (input.length() % 4) // Sanity check
    throw torrent::input_error("Invalid base64.");
  size_t padding = 0;
  if (input.length()) {
    if (input[input.length() - 1] == padCharacter)
      padding++;
    if (input[input.length() - 2] == padCharacter)
      padding++;
  }
  // Setup a vector to hold the result
  std::string decodedBytes;
  decodedBytes.reserve(((input.length() / 4) * 3) - padding);
  long                             temp   = 0; // Holds decoded quanta
  std::string_view::const_iterator cursor = input.begin();
  while (cursor < input.end()) {
    for (size_t quantumPosition = 0; quantumPosition < 4; quantumPosition++) {
      temp <<= 6;
      if (*cursor >= 0x41 && *cursor <= 0x5A) // This area will need tweaking if
        temp |= *cursor - 0x41; // you are using an alternate alphabet
      else if (*cursor >= 0x61 && *cursor <= 0x7A)
        temp |= *cursor - 0x47;
      else if (*cursor >= 0x30 && *cursor <= 0x39)
        temp |= *cursor + 0x04;
      else if (*cursor == 0x2B)
        temp |= 0x3E; // change to 0x2D for URL alphabet
      else if (*cursor == 0x2F)
        temp |= 0x3F;                   // change to 0x5F for URL alphabet
      else if (*cursor == padCharacter) // pad
      {
        switch (input.end() - cursor) {
          case 1: // One pad character
            decodedBytes.push_back((temp >> 16) & 0x000000FF);
            decodedBytes.push_back((temp >> 8) & 0x000000FF);
            return decodedBytes;
          case 2: // Two pad characters
            decodedBytes.push_back((temp >> 10) & 0x000000FF);
            return decodedBytes;
          default:
            throw torrent::input_error("Invalid padding in base64.");
        }
      } else
        throw torrent::input_error("Invalid character in base64.");
      cursor++;
    }
    decodedBytes.push_back((temp >> 16) & 0x000000FF);
    decodedBytes.push_back((temp >> 8) & 0x000000FF);
    decodedBytes.push_back((temp)&0x000000FF);
  }
  return decodedBytes;
}

void
Manager::push_log(const char* msg) {
  m_log_important->lock_and_push_log(msg, strlen(msg), 0);
  m_log_complete->lock_and_push_log(msg, strlen(msg), 0);
}

Manager::Manager()
  : m_log_important(torrent::log_open_log_buffer("important"))
  , m_log_complete(torrent::log_open_log_buffer("complete")) {
  m_downloadStore   = new DownloadStore();
  m_downloadList    = new DownloadList();
  m_fileStatusCache = new FileStatusCache();
  m_httpQueue       = new HttpQueue();
  m_httpStack       = new CurlStack();

  torrent::Throttle* unthrottled = torrent::Throttle::create_throttle();
  unthrottled->set_max_rate(0);
  m_throttles["NULL"] = std::make_pair(unthrottled, unthrottled);
}

Manager::~Manager() {
  torrent::Throttle::destroy_throttle(m_throttles["NULL"].first);
  delete m_downloadList;

  // TODO: Clean up logs objects.

  delete m_downloadStore;
  delete m_httpQueue;
  delete m_fileStatusCache;
}

void
Manager::set_hashing_view(View* v) {
  if (v == nullptr || m_hashingView != nullptr)
    throw torrent::internal_error(
      "Manager::set_hashing_view(...) received nullptr or is already set.");

  m_hashingView = v;
  m_hashingView->signal_changed().push_back(
    std::bind(&Manager::receive_hashing_changed, this));
}

torrent::ThrottlePair
Manager::get_throttle(const std::string& name) {
  ThrottleMap::const_iterator itr = m_throttles.find(name);
  torrent::ThrottlePair       throttles =
    (itr == m_throttles.end() ? torrent::ThrottlePair(nullptr, nullptr)
                              : itr->second);

  if (throttles.first == nullptr)
    throttles.first = torrent::up_throttle_global();

  if (throttles.second == nullptr)
    throttles.second = torrent::down_throttle_global();

  return throttles;
}

void
Manager::set_address_throttle(uint32_t              begin,
                              uint32_t              end,
                              torrent::ThrottlePair throttles) {
  m_addressThrottles.set_merge(begin, end, throttles);
  torrent::connection_manager()->address_throttle() =
    std::bind(&core::Manager::get_address_throttle,
              control->core(),
              std::placeholders::_1);
}

torrent::ThrottlePair
Manager::get_address_throttle(const sockaddr* addr) {
  return m_addressThrottles.get(
    torrent::utils::socket_address::cast_from(addr)->sa_inet()->address_h(),
    torrent::ThrottlePair(nullptr, nullptr));
}

int64_t
Manager::retrieve_throttle_value(const torrent::Object::string_type& name,
                                 bool                                rate,
                                 bool                                up) {
  ThrottleMap::iterator itr = throttles().find(name);

  if (itr == throttles().end()) {
    return (int64_t)-1;
  } else {
    torrent::Throttle* throttle = up ? itr->second.first : itr->second.second;

    // check whether the actual up/down throttle exist (one of the pair can be
    // missing)
    if (throttle == nullptr)
      return (int64_t)-1;

    int64_t throttle_max = (int64_t)throttle->max_rate();

    if (rate) {

      if (throttle_max > 0)
        return (int64_t)throttle->rate()->rate();
      else
        return (int64_t)-1;

    } else {
      return throttle_max;
    }
  }
}

// Most of this should be possible to move out.
void
Manager::initialize_second() {
  torrent::Http::slot_factory() =
    std::bind(&CurlStack::new_object, m_httpStack);
  m_httpQueue->set_slot_factory(std::bind(&CurlStack::new_object, m_httpStack));

  CurlStack::global_init();
}

void
Manager::cleanup() {
  // Need to disconnect log signals? Not really since we won't receive
  // any more.

  m_downloadList->clear();

  // When we implement asynchronous DNS lookups, we need to cancel them
  // here before the torrent::* objects are deleted.

  torrent::cleanup();

  delete m_httpStack;
  CurlStack::global_cleanup();
}

void
Manager::shutdown(bool force) {
  if (!force)
    std::for_each(m_downloadList->begin(),
                  m_downloadList->end(),
                  [this](Download* download) {
                    return m_downloadList->pause_default(download);
                  });
  else
    std::for_each(m_downloadList->begin(),
                  m_downloadList->end(),
                  [this](Download* download) {
                    return m_downloadList->close_quick(download);
                  });
}

void
Manager::listen_open() {
  // This stuff really should be moved outside of manager, make it
  // part of the init script.
  if (!rpc::call_command_value("network.port_open"))
    return;

  int             portFirst, portLast;
  torrent::Object portRange = rpc::call_command("network.port_range");

  if (portRange.is_string()) {
    if (std::sscanf(
          portRange.as_string().c_str(), "%i-%i", &portFirst, &portLast) != 2)
      throw torrent::input_error("Invalid port_range argument.");

    //   } else if (portRange.is_list()) {

  } else {
    throw torrent::input_error("Invalid port_range argument.");
  }

  if (portFirst > portLast || portLast >= (1 << 16))
    throw torrent::input_error("Invalid port range.");

  if (rpc::call_command_value("network.port_random")) {
    int boundary = portFirst + random() % (portLast - portFirst + 1);

    if (torrent::connection_manager()->listen_open(boundary, portLast) ||
        torrent::connection_manager()->listen_open(portFirst, boundary))
      return;

  } else {
    if (torrent::connection_manager()->listen_open(portFirst, portLast))
      return;
  }

  throw torrent::input_error("Could not open/bind port for listening: " +
                             torrent::utils::error_number::current().message());
}

std::string
Manager::bind_address() const {
  return torrent::utils::socket_address::cast_from(
           torrent::connection_manager()->bind_address())
    ->address_str();
}

void
Manager::set_bind_address(const std::string& addr) {
  int                           err;
  torrent::utils::address_info* ai;

  if ((err = torrent::utils::address_info::get_address_info(
         addr.c_str(), PF_INET, SOCK_STREAM, &ai)) != 0 &&
      (err = torrent::utils::address_info::get_address_info(
         addr.c_str(), PF_INET6, SOCK_STREAM, &ai)) != 0)
    throw torrent::input_error(
      "Could not set bind address: " +
      std::string(torrent::utils::address_info::strerror(err)) + ".");

  try {

    if (torrent::connection_manager()->listen_port() != 0) {
      torrent::connection_manager()->listen_close();
      torrent::connection_manager()->set_bind_address(
        ai->address()->c_sockaddr());
      listen_open();

    } else {
      torrent::connection_manager()->set_bind_address(
        ai->address()->c_sockaddr());
    }

    m_httpStack->set_bind_address(!ai->address()->is_address_any()
                                    ? ai->address()->address_str()
                                    : std::string());

    torrent::utils::address_info::free_address_info(ai);

  } catch (torrent::input_error& e) {
    torrent::utils::address_info::free_address_info(ai);
    throw e;
  }
}

std::string
Manager::local_address() const {
  return torrent::utils::socket_address::cast_from(
           torrent::connection_manager()->local_address())
    ->address_str();
}

void
Manager::set_local_address(const std::string& addr) {
  int                           err;
  torrent::utils::address_info* ai;

  if ((err = torrent::utils::address_info::get_address_info(
         addr.c_str(), PF_INET, SOCK_STREAM, &ai)) != 0 &&
      (err = torrent::utils::address_info::get_address_info(
         addr.c_str(), PF_INET6, SOCK_STREAM, &ai)) != 0)
    throw torrent::input_error(
      "Could not set local address: " +
      std::string(torrent::utils::address_info::strerror(err)) + ".");

  try {

    torrent::connection_manager()->set_local_address(
      ai->address()->c_sockaddr());
    torrent::utils::address_info::free_address_info(ai);

  } catch (torrent::input_error& e) {
    torrent::utils::address_info::free_address_info(ai);
    throw e;
  }
}

std::string
Manager::proxy_address() const {
  return torrent::utils::socket_address::cast_from(
           torrent::connection_manager()->proxy_address())
    ->address_str();
}

void
Manager::set_proxy_address(const std::string& addr) {
  int                           port;
  torrent::utils::address_info* ai;

  char* buf = static_cast<char*>(calloc(addr.length() + 1, sizeof(char)));

  int err = std::sscanf(addr.c_str(), "%[^:]:%i", buf, &port);

  if (err <= 0)
    throw torrent::input_error("Could not parse proxy address.");

  if (err == 1)
    port = 80;

  err = torrent::utils::address_info::get_address_info(
    buf, PF_INET, SOCK_STREAM, &ai);

  free(buf);

  if (err != 0)
    throw torrent::input_error(
      "Could not set proxy address: " +
      std::string(torrent::utils::address_info::strerror(err)) + ".");

  try {

    ai->address()->set_port(port);
    torrent::connection_manager()->set_proxy_address(
      ai->address()->c_sockaddr());

    torrent::utils::address_info::free_address_info(ai);

  } catch (torrent::input_error& e) {
    torrent::utils::address_info::free_address_info(ai);
    throw e;
  }
}

void
Manager::receive_http_failed(std::string msg) {
  push_log_std("Http download error: \"" + msg + "\"");
}

torrent::Object
Manager::try_create_download(const std::string&       uri,
                             int                      flags,
                             const command_list_type& commands) {
  auto result = torrent::Object::create_value();

  // If the path was attempted loaded before, skip it.
  if ((flags & create_tied) && !(flags & create_raw_data) &&
      !is_network_uri(uri) && !is_magnet_uri(uri) && !is_data_uri(uri) &&
      !file_status_cache()->insert(uri, flags & create_throw))
    return result;

  // Adding download.
  DownloadFactory* f = new DownloadFactory(this);

  f->variables()["tied_to_file"] = (int64_t)(bool)(flags & create_tied);
  f->commands().insert(f->commands().end(), commands.begin(), commands.end());

  f->set_start(flags & create_start);
  f->set_print_log(!(flags & create_quiet));

  if (flags & create_throw) {
    f->set_immediate(true);
    f->slot_finished([f, &result]() {
      result = f->result();
      delete f;
    });
  } else {
    f->slot_finished([f]() { delete f; });
  }

  if (flags & create_raw_data) {
    f->load_raw_data(uri);
  } else if (is_data_uri(uri)) {
    const unsigned long start = uri.find("base64,", 5) + 7;
    if (start >= uri.size()) {
      throw torrent::input_error("Empty base64.");
    }

    f->load_raw_data(base64Decode(std::string_view(uri.c_str() + start)));
    f->variables()["tied_to_file"] = (int64_t)0;
  } else {
    f->load(uri);
  }

  f->commit();

  return result;
}

void
Manager::try_create_download_from_meta_download(torrent::Object*   bencode,
                                                const std::string& metafile) {
  DownloadFactory* f = new DownloadFactory(this);

  f->variables()["tied_to_file"] = (int64_t) true;
  f->variables()["tied_file"]    = metafile;

  torrent::Object&            meta = bencode->get_key("rtorrent_meta_download");
  torrent::Object::list_type& commands = meta.get_key_list("commands");
  for (torrent::Object::list_type::const_iterator itr = commands.begin();
       itr != commands.end();
       ++itr)
    f->commands().insert(f->commands().end(), itr->as_string());

  f->set_start(meta.get_key_value("start"));
  f->set_print_log(meta.get_key_value("print_log"));
  f->slot_finished([f]() { delete f; });

  // Bit of a waste to create the bencode representation here
  // only to have the DownloadFactory decode it.
  std::stringstream s;
  s.imbue(std::locale::classic());
  s << *bencode;
  f->load_raw_data(s.str());
  f->commit();
}

utils::Directory
path_expand_transform(std::string path, const utils::directory_entry& entry) {
  return path + entry.d_name;
}

// Move this somewhere better.
void
path_expand(std::vector<std::string>* paths, const std::string& pattern) {
  glob_t glob_result;

  glob(pattern.c_str(), GLOB_TILDE, nullptr, &glob_result);

  for (unsigned int i = 0; i < glob_result.gl_pathc; i++) {
    std::string     resolved_path;
    std::error_code error;

    resolved_path = std::filesystem::absolute(glob_result.gl_pathv[i], error)
                      .lexically_normal();

    if (!error) {
      paths->push_back(resolved_path);
    }
  }

  globfree(&glob_result);
}

bool
manager_equal_tied(const std::string& path, Download* download) {
  return path ==
         rpc::call_command_string("d.tied_to_file", rpc::make_target(download));
}

torrent::Object
Manager::try_create_download_expand(const std::string& uri,
                                    int                flags,
                                    command_list_type  commands) {
  torrent::Object             rawResult = torrent::Object::create_list();
  torrent::Object::list_type& result    = rawResult.as_list();

  if (flags & create_raw_data) {
    result.push_back(try_create_download(uri, flags, commands));
  } else {
    std::vector<std::string> paths;

    path_expand(&paths, uri);

    if (!paths.empty()) {
      for (const auto& path : paths) {
        result.push_back(try_create_download(path, flags, commands));
      }
    } else {
      result.push_back(try_create_download(uri, flags, commands));
    }
  }

  if (result.size() == 0 || result[0].type() != torrent::Object::TYPE_STRING) {
    // return "0" instead of the array if the request is asynchronous
    return torrent::Object();
  }

  return rawResult;
}

// DownloadList's hashing related functions don't actually start the
// hashing, it only reacts to events. This functions checks the
// hashing view and starts hashing if necessary.
void
Manager::receive_hashing_changed() {
  bool foundHashing = std::find_if(m_hashingView->begin_visible(),
                                   m_hashingView->end_visible(),
                                   std::mem_fn(&Download::is_hash_checking)) !=
                      m_hashingView->end_visible();

  // Try quick hashing all those with hashing == initial, set them to
  // something else when failed.
  for (View::iterator itr  = m_hashingView->begin_visible(),
                      last = m_hashingView->end_visible();
       itr != last;
       ++itr) {
    if ((*itr)->is_hash_checked())
      throw torrent::internal_error(
        "core::Manager::receive_hashing_changed() (*itr)->is_hash_checked().");

    if ((*itr)->is_hash_checking() || (*itr)->is_hash_failed())
      continue;

    bool tryQuick =
      rpc::call_command_value("d.hashing", rpc::make_target(*itr)) ==
        Download::variable_hashing_initial &&
      (*itr)->download()->file_list()->bitfield()->empty();

    if (!tryQuick && foundHashing)
      continue;

    try {
      m_downloadList->open_throw(*itr);

      // Since the bitfield is allocated on loading of resume load or
      // hash start, and unallocated on close, we know that if it it
      // not empty then we have already loaded any existing resume
      // data.
      if ((*itr)->download()->file_list()->bitfield()->empty())
        torrent::resume_load_progress(
          *(*itr)->download(),
          (*itr)->download()->bencode()->get_key("libtorrent_resume"));

      if (tryQuick) {
        if ((*itr)->download()->hash_check(true))
          continue;

        (*itr)->download()->hash_stop();

        if (foundHashing) {
          rpc::call_command_set_value("d.hashing.set",
                                      Download::variable_hashing_rehash,
                                      rpc::make_target(*itr));
          continue;
        }
      }

      (*itr)->download()->hash_check(false);
      foundHashing = true;

    } catch (torrent::local_error& e) {
      if (tryQuick) {
        // Make sure we don't repeat the quick hashing.
        rpc::call_command_set_value("d.hashing.set",
                                    Download::variable_hashing_rehash,
                                    rpc::make_target(*itr));

      } else {
        (*itr)->set_hash_failed(true);
        lt_log_print(
          torrent::LOG_TORRENT_ERROR, "Hashing failed: %s", e.what());
      }
    }
  }
}

}
