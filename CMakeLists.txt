cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
cmake_policy(SET CMP0074 NEW)

# Project information
project(
  "rtorrent"
  DESCRIPTION "rTorrent BitTorrent client"
  VERSION 0.9.8
  LANGUAGES CXX C)

# API version information
set(API_VERSION 10)

# Options
option(BUILDINFO_ONLY "Generate buildinfo.h only" OFF)
option(USE_EXTRA_DEBUG "Enable extra debugging checks" OFF)
option(USE_RUNTIME_CA_DETECTION "Enable runtime detection of path to CA bundle" ON)
option(USE_XMLRPC "Enable XML-RPC interface" ON)

# Include CMake modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Compiler options - Common
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options("-Wall" "-Wextra" "-Wpedantic")

# Compiler options - Optimizations
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_compile_options("-Og")
else()
  if(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
    add_compile_options("-Os")
  else()
    add_compile_options("-O3")
  endif()
endif()

# Compiler options - Debug information
if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL
                                        "RelWithDebInfo")
  add_compile_options("-g")
else()
  add_compile_options("-flto")
  add_link_options("-flto" "-s")
endif()

# Use GNU install destinations
include(GNUInstallDirs)

# Generate buildinfo.h
include(GenerateRTorrentBuildinfo)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include ${CMAKE_BINARY_DIR}/include)

if(BUILDINFO_ONLY)
  install(FILES ${CMAKE_BINARY_DIR}/include/buildinfo.h
          DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
else()
  # Required packages
  find_package(CURL REQUIRED)
  include_directories(${CURL_INCLUDE_DIRS})

  set(CURSES_NEED_WIDE ON)
  find_package(Curses)
  if(NOT CURSES_FOUND)
    set(CURSES_NEED_WIDE OFF)
    find_package(Curses REQUIRED)
  endif()
  include_directories(${CURSES_INCLUDE_DIRS})

  if(USE_XMLRPC)
    find_package(XMLRPC REQUIRED c++)
    include_directories(${XMLRPC_INCLUDE_DIRS})
  endif()

  file(GLOB_RECURSE RTORRENT_COMMON_SRCS "${PROJECT_SOURCE_DIR}/src/*.cc")
  list(REMOVE_ITEM RTORRENT_COMMON_SRCS "${PROJECT_SOURCE_DIR}/src/main.cc")

  # common objects
  find_package(Torrent REQUIRED)
  include_directories(${TORRENT_INCLUDE_DIR})
  add_library(rtorrent_common OBJECT ${RTORRENT_COMMON_SRCS})
  target_link_libraries(rtorrent_common ${TORRENT_LIBRARY} ${CURL_LIBRARIES}
                        ${CURSES_LIBRARIES})
  if(USE_XMLRPC)
    target_link_libraries(rtorrent_common ${XMLRPC_LIBRARIES})
  endif()

  # rtorrent
  add_executable(rtorrent "${PROJECT_SOURCE_DIR}/src/main.cc")
  target_link_libraries(rtorrent rtorrent_common)
  install(TARGETS rtorrent RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

  # tests
  set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
  set(THREADS_PREFER_PTHREAD_FLAG TRUE)
  find_package(GTest)
  find_package(Threads)
  if(GTest_FOUND AND Threads_FOUND)
    enable_testing()
    file(GLOB_RECURSE RTORRENT_TEST_SRCS "${PROJECT_SOURCE_DIR}/test/*.cc")
    add_executable(rtorrent_test ${RTORRENT_TEST_SRCS})
    find_package(Threads REQUIRED)
    include_directories(${GTEST_INCLUDE_DIRS})
    target_link_libraries(rtorrent_test rtorrent_common ${GTEST_LIBRARIES} Threads::Threads)
    gtest_discover_tests(rtorrent_test)
  endif()
endif()
