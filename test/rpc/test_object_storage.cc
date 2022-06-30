#include "test/rpc/object_storage_test.h"
#include "test/helpers/assert.h"

TEST_F(ObjectStorageTest, test_basics) {
  rpc::object_storage::iterator itr;

  ASSERT_TRUE(m_storage.empty());

  itr = m_storage.insert(
    "test_1", torrent::Object("a"), rpc::object_storage::flag_string_type);

  ASSERT_TRUE(itr != m_storage.end());
  ASSERT_TRUE(itr->first.size() == 6 &&
              std::strcmp(itr->first.data(), "test_1") == 0);
  ASSERT_TRUE(itr->second.object.is_string() &&
              itr->second.object.as_string() == "a");

  ASSERT_CATCH_INPUT_ERROR({
    m_storage.insert(
      "test_1", torrent::Object("a"), rpc::object_storage::flag_string_type);
  });

  // Test erase.
  m_storage.erase(rpc::object_storage::key_type::from_c_str("test_1"));
  ASSERT_TRUE(m_storage.empty());

  // Test with no type flag.
  ASSERT_CATCH_INPUT_ERROR(
    { m_storage.insert("test_2", torrent::Object("b"), 0); });
  ASSERT_CATCH_INPUT_ERROR({
    m_storage.insert(
      "test_3", torrent::Object("c"), ~rpc::object_storage::mask_type);
  });

  m_storage.clear();
}

TEST_F(ObjectStorageTest, test_conversions) {
  ASSERT_TRUE(m_storage.insert("test_1",
                               torrent::Object("a"),
                               rpc::object_storage::flag_string_type) !=
              m_storage.end());
  ASSERT_TRUE(m_storage.insert_str(std::string("test_2"),
                                   torrent::Object("a"),
                                   rpc::object_storage::flag_string_type) !=
              m_storage.end());

  char                raw_3[8] = "test_3\x1";
  torrent::raw_string raw_string_3(raw_3, 6);

  ASSERT_TRUE(m_storage
                .insert(raw_string_3,
                        torrent::Object("a"),
                        rpc::object_storage::flag_string_type)
                ->first == std::string("test_3"));
  m_storage.clear();
}

TEST_F(ObjectStorageTest, test_validate_keys) {
  torrent::raw_string raw_string_4("test_4\0foo", 10);

  ASSERT_CATCH_INPUT_ERROR({
    m_storage.insert(raw_string_4,
                     torrent::Object("a"),
                     rpc::object_storage::flag_string_type);
  });
}

// And test many other bad/good string combos.

// Test for various conversions of fixed_key_type.

TEST_F(ObjectStorageTest, test_access) {
  m_storage.insert("string_1",
                   torrent::Object("gen_a"),
                   rpc::object_storage::flag_string_type);
  m_storage.insert("value_1", int64_t(1), rpc::object_storage::flag_value_type);

  ASSERT_TRUE(m_storage.get_c_str("string_1").as_string() == "gen_a");
  ASSERT_TRUE(m_storage.set_c_str_string("string_1", "test").as_string() ==
              "test");

  // Test value from raw and normal, list, etc.
  ASSERT_TRUE(m_storage.get_c_str("value_1").as_value() == 1);
  ASSERT_TRUE(m_storage.set_c_str_value("value_1", int64_t(2)).as_value() == 2);
  //  ASSERT_TRUE(m_storage.set_c_str_value("value_1", "123").as_value() ==
  //  123); ASSERT_TRUE(m_storage.set_c_str_value("value_1",
  //  torrent::raw_string::from_c_str("321")).as_value() == 321);
  //  ASSERT_TRUE(m_storage.set_c_str_value("value_1",
  //  torrent::raw_bencode::from_c_str("i567e")).as_value() == 567);

  //  ASSERT_CATCH_INPUT_ERROR( { m_storage.set_c_str_value("value_1", "e123");
  //  } );

  // Test string from raw and normal, list, etc.
}
