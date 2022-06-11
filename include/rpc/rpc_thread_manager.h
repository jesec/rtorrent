#ifndef RTORRENT_RPC_THREAD_MANAGER_H
#define RTORRENT_RPC_THREAD_MANAGER_H

#include "thread_worker.h"
#include "websockets_thread.h"

class RpcThreadManager {
public:

    ~RpcThreadManager();

    std::pair<bool, bool> is_active() const;

    void* scgi_protocol();

    void* websockets_protocol();

    bool set_scgi_protocol(void* scgi);

    bool set_websockets_protocol(void* websockets);

    void init_thread();

    void start_thread();

    void set_rpc_log(const std::string& filename);

    void queue_item(void* newFunc);

    torrent::Poll* poll();
    
private:

    ThreadWorker* m_thread_worker = new ThreadWorker();
    WebsocketsThread* m_websockets_thread = new WebsocketsThread();
    
};

#endif //RTORRENT_RPC_THREAD_MANAGER_H