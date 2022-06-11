#include "rpc/rpc_thread_manager.h"

RpcThreadManager::~RpcThreadManager() {
  delete m_websockets_thread;
  delete m_thread_worker;
}

std::pair<bool, bool> RpcThreadManager::is_active() const {
  return std::pair<bool, bool> {m_thread_worker->is_active(), m_websockets_thread->is_active()};
}

void* RpcThreadManager::scgi_protocol() {
  return m_thread_worker->protocol();
}

void* RpcThreadManager::websockets_protocol() {
  return m_websockets_thread->protocol();
}

bool RpcThreadManager::set_scgi_protocol(void* scgi) {
  return m_thread_worker->set_protocol(scgi);
}

bool RpcThreadManager::set_websockets_protocol(void* websockets) {
  return m_websockets_thread->set_protocol(websockets);
}

void RpcThreadManager::init_thread() {
  m_thread_worker->init_thread();
}

void RpcThreadManager::start_thread() {
  m_thread_worker->start_thread();
  m_websockets_thread->start_thread();
}

void RpcThreadManager::set_rpc_log(const std::string& filename) {
  m_thread_worker->set_rpc_log(filename);
  m_websockets_thread->set_rpc_log(filename);
}

void RpcThreadManager::queue_item(void* newFunc) {
  m_thread_worker->queue_item(newFunc);
  m_websockets_thread->queue_item(newFunc);
}

torrent::Poll* RpcThreadManager::poll() {
  return m_thread_worker->poll();
}