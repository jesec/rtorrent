// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_RPC_RPC_XML_H
#define RTORRENT_RPC_RPC_XML_H

#include <functional>

#include "rpc/rpc.h"

namespace rpc {

class RpcXml final : public IRpc {
public:
  void initialize() override;

  void cleanup() override;

  bool is_valid() const override {
    return m_env != nullptr;
  }

  bool process(const char*  inBuffer,
               uint32_t     length,
               res_callback callback) override;

  void insert_command(const char* name,
                      const char* parm,
                      const char* doc) override;

private:
  void* m_env{ nullptr };
  void* m_registry{ nullptr };
};

}

#endif
