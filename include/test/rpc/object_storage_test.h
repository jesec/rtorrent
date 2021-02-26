#include <gtest/gtest.h>

#include "rpc/object_storage.h"

class ObjectStorageTest : public ::testing::Test {
public:
  rpc::object_storage m_storage;
};
