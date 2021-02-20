// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_RPC_FIXED_KEY_H
#define RTORRENT_RPC_FIXED_KEY_H

#include <torrent/object_raw_bencode.h>

namespace rpc {

// The key size should be such that the value type size which includes
// the next-pointer.

template<size_t MaxSize>
class fixed_key_type {
public:
  using value_type     = char;
  using iterator       = const char*;
  using const_iterator = const char*;
  using size_type      = uint32_t;

  static constexpr size_type max_size = MaxSize - 1;

  fixed_key_type() {
    m_data[0] = '\0';
  }
  fixed_key_type(const fixed_key_type& k)
    : m_size(k.m_size) {
    std::memcpy(m_data, k.m_data, k.m_size + 1);
  }

  fixed_key_type(const value_type* src_data, size_type src_size) {
    set_data(src_data, src_size);
  }

  static fixed_key_type from_c_str(const char* str) {
    fixed_key_type k;
    k.set_c_str(str);
    return k;
  }
  static fixed_key_type from_string(const std::string& str) {
    fixed_key_type k;
    k.set_c_str(str.c_str(), str.size());
    return k;
  }
  static fixed_key_type from_raw_string(const torrent::raw_string& str) {
    fixed_key_type k;
    k.set_data(str.data(), str.size());
    return k;
  }

  bool empty() const {
    return m_size == 0;
  }
  size_type size() const {
    return m_size;
  }

  iterator begin() const {
    return m_data;
  }
  iterator end() const {
    return m_data + m_size;
  }

  value_type* data() {
    return m_data;
  }
  const value_type* data() const {
    return m_data;
  }
  const char* c_str() const {
    return m_data;
  }

  void set_data(const value_type* src_data, size_type src_size);
  void set_c_str(const value_type* src_data);
  void set_c_str(const value_type* src_data, size_type src_size);

  bool operator==(const fixed_key_type& rhs) const {
    return m_size == rhs.m_size && std::memcmp(m_data, rhs.m_data, m_size) == 0;
  }
  bool operator!=(const fixed_key_type& rhs) const {
    return m_size != rhs.m_size || std::memcmp(m_data, rhs.m_data, m_size) != 0;
  }

  bool operator==(const torrent::raw_string& rhs) const {
    return m_size == rhs.size() && std::memcmp(m_data, rhs.data(), m_size) == 0;
  }
  bool operator!=(const torrent::raw_string& rhs) const {
    return m_size != rhs.size() || std::memcmp(m_data, rhs.data(), m_size) != 0;
  }

  bool operator==(const std::string& rhs) const {
    return m_size == rhs.size() && std::memcmp(m_data, rhs.data(), m_size) == 0;
  }

private:
  size_type m_size{ 0 };
  char      m_data[max_size];
};

struct hash_fixed_key_type {
  template<size_t MaxSize>
  inline std::size_t operator()(const fixed_key_type<MaxSize>& p) const {
    return hash(p.data());
  }

  static inline std::size_t hash(const char* data) {
    std::size_t result = 0;

    while (*data != '\0')
      result = (result * 131) + *data++;

    return result;
  }

  static inline std::size_t hash(const char* data, uint32_t size) {
    std::size_t result = 0;

    while (size--)
      result = (result * 131) + *data++;

    return result;
  }
};

template<size_t MaxSize>
bool
operator==(const torrent::raw_string& lhs, const fixed_key_type<MaxSize>& rhs) {
  return lhs.size() == rhs.size() &&
         std::memcmp(lhs.data(), rhs.data(), lhs.size()) == 0;
}

}

#endif
