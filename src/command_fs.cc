// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2020, Contributors to the rTorrent project

#include <filesystem>
#include <string>

#include "command_helpers.h"

torrent::Object
homedir(bool nothrow) {
  char* val = getenv("HOME");

  if (nothrow) {
    return std::string(val ? val : "");
  }

  if (!val) {
    throw torrent::input_error("Failed to get home directory");
  }

  return std::string(val);
}

torrent::Object
mkdir(const torrent::Object::string_type& path, bool recursive, bool nothrow) {
  std::error_code error;

  if (recursive) {
    std::filesystem::create_directories(path, error);
  } else {
    std::filesystem::create_directory(path, error);
  }

  if (nothrow) {
    return -error.value();
  }

  if (error) {
    throw torrent::input_error(error.message());
  }

  return error.value();
}

void
initialize_command_fs() {
  CMD2_ANY("fs.homedir", std::bind(&homedir, false));
  CMD2_ANY("fs.homedir.nothrow", std::bind(&homedir, true));

  CMD2_ANY_STRING("fs.mkdir",
                  std::bind(&mkdir, std::placeholders::_2, false, false));
  CMD2_ANY_STRING("fs.mkdir.nothrow",
                  std::bind(&mkdir, std::placeholders::_2, true, true));
  CMD2_ANY_STRING("fs.mkdir.recursive",
                  std::bind(&mkdir, std::placeholders::_2, true, false));
  CMD2_ANY_STRING("fs.mkdir.recursive.nothrow",
                  std::bind(&mkdir, std::placeholders::_2, true, true));
}
