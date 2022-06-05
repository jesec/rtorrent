#include "websockets_thread.h"

#include "globals.h"
#include "control.h"
#include "core/manager.h"

#include <torrent/utils/path.h>
#include <fcntl.h>

using namespace uWS;

WebsocketsThread::~WebsocketsThread() {

  delete listen_info;
  delete m_websockets_app;

  if (m_websockets_thread->joinable()) {
    m_websockets_thread->join();
  }
}

bool
WebsocketsThread::set_protocol(void* websockets) {
  listen_info = static_cast<std::pair<std::string, int>*>(websockets);
  return true;
}

void
WebsocketsThread::set_rpc_log(const std::string &filename) {
  m_rpcLog = filename;

  torrent::thread_base::acquire_global_lock();

  if (m_log_fd != -1) {
    ::close(m_log_fd);
    m_log_fd = -1;
    control->core()->push_log("Closed RPC log.");
  }
  if (m_rpcLog.empty()) return;
  m_log_fd = open(torrent::utils::path_expand(m_rpcLog).c_str(),
                  O_WRONLY | O_APPEND | O_CREAT,
                  0644);
  if (m_log_fd == -1) {
    control->core()->push_log_std("Could not open RPC log file '" + m_rpcLog + "'.");
    return;
  }
  control->core()->push_log_std("Logging RPC events to '" + m_rpcLog + "'.");

  torrent::thread_base::release_global_lock();
}

void
WebsocketsThread::queue_item(void*) {
  // The follow statement will not create a new thread as it doesn't init and start.
  // it just uses to exit the process gracefully (according to src/control.cc Control::handle_shutdown())
  worker_thread = new ThreadWorker;
  worker_thread->queue_item((void*)ThreadBase::stop_thread);
}

void
WebsocketsThread::start_thread() {
  auto create_ws_server_and_run = [&]() {
    m_websockets_app = new App();

    App::WebSocketBehavior<ConnectionData> behavior;
    behavior.open = [&](WebSocket<false, true, ConnectionData>* ws) {
      ws->getUserData()->address = ws->getRemoteAddressAsText();
    };
    behavior.message = [&](WebSocket<false, true, ConnectionData>* ws, std::string_view request, OpCode) {
      m_websocket_connection = ws;
      handle_request(request);
    };

    m_websockets_app->ws("/*", std::move(behavior));

    if (listen_info->second == 1) {
      auto ip_port = listen_info->first;
      const auto& delim_pos = ip_port.find_first_of(':');
      auto ip = ip_port.substr(0, delim_pos);
      auto port = std::stoi(ip_port.substr(delim_pos + 1));
      m_websockets_app->listen(ip, port, [&](us_listen_socket_t* listen_socket) {
        m_listen_socket = listen_socket;
      });
    }
    else {
      m_websockets_app->listen_unix(listen_info->first, [&](us_listen_socket_t* listen_socket) {
        m_listen_socket = listen_socket;
      });
    }

    m_loop = Loop::get();

    if (m_listen_socket) m_websockets_app->run();
    else throw torrent::internal_error("Can't make websockets server run !!!");
  };

  m_websockets_thread = std::make_unique<std::thread>(create_ws_server_and_run);
  m_thread_id = m_websockets_thread->get_id();
}

void
WebsocketsThread::handle_request(const std::string_view& request) {
  rpc::rpc.dispatch(rpc::RpcManager::RPCType::JSON, request.data(), request.length(), [&](const char* response, uint32_t) {
    return m_websocket_connection->send(std::string_view(response), uWS::OpCode::TEXT);
  });
}