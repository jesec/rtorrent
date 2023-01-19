// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <functional>
#include <getopt.h>
#include <stdexcept>
#include <unistd.h>
#include <utility>

#include "option_parser.h"

void
OptionParser::insert_flag(char c, slot_string s) {
  m_container[c].m_slot      = std::move(s);
  m_container[c].m_useOption = false;
}

void
OptionParser::insert_option(char c, slot_string s) {
  m_container[c].m_slot      = std::move(s);
  m_container[c].m_useOption = true;
}

void
OptionParser::insert_option_list(char c, slot_string_pair s) {
  m_container[c].m_slot = [s = std::move(s)](const auto& arg) {
    return OptionParser::call_option_list(s, arg);
  };
  m_container[c].m_useOption = true;
}

void
OptionParser::insert_int_pair(char c, slot_int_pair s) {
  m_container[c].m_slot = [s = std::move(s)](const auto& arg) {
    return OptionParser::call_int_pair(s, arg);
  };
  m_container[c].m_useOption = true;
}

int
OptionParser::process(int argc, char** argv) {
  int         c;
  std::string optString = create_optstring();

  while ((c = getopt(argc, argv, optString.c_str())) != -1)
    if (c == '?')
      throw std::runtime_error("Invalid/unknown option flag \"-" +
                               std::string(1, (char)optopt) +
                               "\". See rtorrent -h for more information.");
    else
      call(c, optarg ? optarg : "");

  return optind;
}

bool
OptionParser::has_flag(char flag, int argc, char** argv) {
  char options[3] = { '-', flag, '\0' };

  return std::find_if(argv,
                      argv + argc,
                      std::not_fn<std::function<int(const char*)>>(
                        [options](const char* s) {
                          return std::strcmp(options, s);
                        })) != argv + argc;
}

std::string
OptionParser::create_optstring() {
  std::string s;

  for (Container::iterator itr = m_container.begin(); itr != m_container.end();
       ++itr) {
    s += itr->first;

    if (itr->second.m_useOption)
      s += ':';
  }

  return s;
}

void
OptionParser::call(char c, const std::string& arg) {
  Container::iterator itr = m_container.find(c);

  if (itr == m_container.end())
    throw std::logic_error(
      "OptionParser::call_flag(...) could not find the flag");

  itr->second.m_slot(arg);
}

void
OptionParser::call_option_list(slot_string_pair slot, const std::string& arg) {
  std::string::const_iterator itr = arg.begin();

  while (itr != arg.end()) {
    std::string::const_iterator last = std::find(itr, arg.end(), ',');
    std::string::const_iterator opt  = std::find(itr, last, '=');

    if (opt == itr || opt == last)
      throw std::logic_error("Invalid argument, \"" + arg +
                             "\" should be \"key1=opt1,key2=opt2,...\"");

    slot(std::string(itr, opt), std::string(opt + 1, last));

    if (last == arg.end())
      break;

    itr = ++last;
  }
}

void
OptionParser::call_int_pair(slot_int_pair slot, const std::string& arg) {
  int a, b;

  if (std::sscanf(arg.c_str(), "%d-%d", &a, &b) != 2)
    throw std::runtime_error("Invalid argument, \"" + arg +
                             "\" should be \"a-b\"");

  slot(a, b);
}
