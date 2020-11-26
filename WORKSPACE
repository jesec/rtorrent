workspace(name = "rtorrent")

load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

git_repository(
    name = "libtorrent",
    branch = "master",
    remote = "https://github.com/jesec/libtorrent.git",
)

load("@libtorrent//:libtorrent_deps.bzl", "libtorrent_deps")

libtorrent_deps()

http_archive(
    name = "curl",
    build_file = "@rtorrent//:third_party/curl.BUILD",
    sha256 = "01ae0c123dee45b01bbaef94c0bc00ed2aec89cb2ee0fd598e0d302a6b5e0a98",
    strip_prefix = "curl-7.69.1",
    urls = [
        "https://github.com/curl/curl/releases/download/curl-7_69_1/curl-7.69.1.tar.gz",
        "https://curl.haxx.se/download/curl-7.69.1.tar.gz",
    ],
)

http_archive(
    name = "ncurses",
    build_file = "@rtorrent//:third_party/ncurses.BUILD",
    sha256 = "30306e0c76e0f9f1f0de987cf1c82a5c21e1ce6568b9227f7da5b71cbea86c9d",
    strip_prefix = "ncurses-6.2",
    urls = [
        "https://ftp.gnu.org/gnu/ncurses/ncurses-6.2.tar.gz",
        "https://invisible-mirror.net/archives/ncurses/ncurses-6.2.tar.gz",
    ],
)

# MacOS workarounds
_MACOS_CPPUNIT = """
load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
  name = "cppunit",
  srcs = ["lib/libcppunit.dylib"],
  hdrs = glob(["include/cppunit/**"]),
  includes = ["include"],
  visibility = ["//visibility:public"],
)
"""

new_local_repository(
    name = "cppunit",
    build_file_content = _MACOS_CPPUNIT,
    path = "/usr/local/opt/cppunit",
)

_MACOS_XMLRPC = """
load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
  name = "xmlrpc",
  srcs = [
      "lib/libxmlrpc_server.a",
      "lib/libxmlrpc.a",
      "lib/libxmlrpc_util.a",
  ],
  hdrs = glob(["include/**/*"]),
  includes = ["include"],
  visibility = ["//visibility:public"],
)
"""

new_local_repository(
    name = "xmlrpc",
    build_file_content = _MACOS_XMLRPC,
    path = "/usr/local/opt/xmlrpc-c",
)

_MACOS_XML2 = """
load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
  name = "xml2",
  srcs = [
      "lib/libxml2.a",
  ],
  hdrs = glob(["include/libxml2/**"]),
  includes = ["include"],
  visibility = ["//visibility:public"],
)
"""

new_local_repository(
    name = "xml2",
    build_file_content = _MACOS_XML2,
    path = "/usr/local/opt/libxml2",
)
