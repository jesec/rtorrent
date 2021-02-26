#include <gtest/gtest.h>

#include "rpc/command_map.h"

class CommandMapTest : public ::testing::Test {
public:
  static constexpr int cmd_size = 256;

  void SetUp() override {
    m_commandItr = m_commands;
  }

  rpc::CommandMap m_map;

  rpc::command_base  m_commands[cmd_size];
  rpc::command_base* m_commandItr;
};
