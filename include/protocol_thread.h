#ifndef RTORRENT_PROTOCOL_THREAD_H
#define RTORRENT_PROTOCOL_THREAD_H

#include <torrent/exceptions.h>
#include <string>

class ProtocolThread {
public:

  virtual ~ProtocolThread() = default;

  virtual const char* name() const {
    throw torrent::internal_error("No Protocol!");
  }

  virtual bool is_active() const {
    throw torrent::internal_error("ProtocolThread::is_active() No Implemented!");
  }

  virtual void* protocol() {
    throw torrent::internal_error("ProtocolThread::protocol() No Implemented!");
  }

  virtual bool set_protocol(void*) {
    throw torrent::internal_error("ProtocolThread::set_protocol() No Implemented!");
  }

  virtual void init_thread() {
    throw torrent::internal_error("ProtocolThread::init_thread() No Implemented!");
  }

  virtual void start_thread() {
    throw torrent::internal_error("ProtocolThread::start_thread() No Implemented!");
  }

  virtual void set_rpc_log(const std::string&) {
    throw torrent::internal_error("ProtocolThread::set_rpc_log() No Implemented!");
  }

  virtual void queue_item(void*) {
    throw torrent::internal_error("ProtocolThread::queue_item() No Implemented!");
  }

  virtual torrent::Poll* poll() {
    throw torrent::internal_error("ProtocolThread::poll() No Implemented!");
  }

protected:
  // The following types shall only be modified while holding the global lock.
  std::string m_rpcLog;
};

#endif