#ifndef RTORRENT_WEBSOCKETS_THREAD_H
#define RTORRENT_WEBSOCKETS_THREAD_H

#include "protocol_thread.h"
#include "rpc/rpc_manager.h"
#include "rpc/parse_commands.h"

#include <torrent/utils/cacheline.h>
#include <torrent/utils/thread_base.h>
#include <torrent/poll.h>

#include <uWebSockets/App.h>

struct ConnectionData {
  std::string_view address;
  ConnectionData() = default;
};

class lt_cacheline_aligned WebsocketsThread : public ProtocolThread {

public:

  ~WebsocketsThread() override;

  const char* name() const override {
    return "rtorrent websockets";
  }

  bool is_active() const override {
    return m_listen_socket != nullptr;
  }

  void* protocol() override {
    return listen_info;
  }

  bool set_protocol(void*) override;

  void init_thread() override {};

  void start_thread() override;

  void set_rpc_log(const std::string& filename) override;

  void queue_item(void*) override;

private:

  std::unique_ptr<std::thread> m_websockets_thread = nullptr;
  std::thread::id m_thread_id = std::this_thread::get_id();

  uWS::App* lt_cacheline_aligned m_websockets_app = nullptr;

  uWS::WebSocket<false, true, ConnectionData>* m_websocket_connection;

  us_listen_socket_t* m_listen_socket = nullptr;
  uWS::Loop* m_loop = nullptr;

  int m_log_fd = -1;

  std::pair<std::string, int>* listen_info = nullptr;

  std::vector<uWS::WebSocket<false, true, ConnectionData>*> all_connection;

  void handle_request(const std::string_view&);
};

#endif

