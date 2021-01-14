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
    name = "bazel_skylib",
    sha256 = "1c531376ac7e5a180e0237938a2536de0c54d93f5c278634818e0efc952dd56c",
    urls = [
        "https://github.com/bazelbuild/bazel-skylib/releases/download/1.0.3/bazel-skylib-1.0.3.tar.gz",
        "https://mirror.bazel.build/github.com/bazelbuild/bazel-skylib/releases/download/1.0.3/bazel-skylib-1.0.3.tar.gz",
    ],
)

load("@bazel_skylib//:workspace.bzl", "bazel_skylib_workspace")

bazel_skylib_workspace()

http_archive(
    name = "rules_foreign_cc",
    strip_prefix = "rules_foreign_cc-master",
    url = "https://github.com/bazelbuild/rules_foreign_cc/archive/master.zip",
)

load("@rules_foreign_cc//:workspace_definitions.bzl", "rules_foreign_cc_dependencies")

rules_foreign_cc_dependencies()

http_archive(
    name = "cares",
    build_file = "@rtorrent//:third_party/cares/cares.BUILD",
    sha256 = "6cdb97871f2930530c97deb7cf5c8fa4be5a0b02c7cea6e7c7667672a39d6852",
    strip_prefix = "c-ares-1.15.0",
    urls = [
        "https://github.com/c-ares/c-ares/releases/download/cares-1_15_0/c-ares-1.15.0.tar.gz",
    ],
)

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

# Foreign CC dependencies
all_content = """filegroup(name = "all", srcs = glob(["**"]), visibility = ["//visibility:public"])"""

http_archive(
    name = "xmlrpc",
    build_file_content = all_content,
    sha256 = "06dcd87d9c88374559369ffbe83b3139cf41418c1a2d03f20e08808085f89fd0",
    strip_prefix = "xmlrpc-c-1.51.06",
    urls = ["https://downloads.sourceforge.net/project/xmlrpc-c/Xmlrpc-c%20Super%20Stable/1.51.06/xmlrpc-c-1.51.06.tgz"],
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
