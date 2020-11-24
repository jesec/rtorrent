load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")

COPTS = [
    "-std=c++17",
    "-Ofast",
    "-Wall",
    "-Wextra",
    "-faligned-new",
    "-flto",
]

LINKOPTS = [
    "-O3",
    "-flto",
    "-s",
]

genrule(
    name = "buildinfo",
    srcs = [
        "CMakeLists.txt",
    ] + glob([
        "cmake/**/*",
        "**/*.in",
    ]),
    outs = ["include/buildinfo.h"],
    cmd = "cmake -S $$(dirname $(location CMakeLists.txt)) -B $(RULEDIR) -DBUILDINFO_ONLY=ON",
)

filegroup(
    name = "included_headers",
    srcs = ["include/buildinfo.h"] + glob(["include/**/*.h"]),
)

cc_library(
    name = "rtorrent_common",
    srcs = glob(
        ["src/**/*.cc"],
        exclude = ["src/main.cc"],
    ) + ["//:included_headers"],
    copts = COPTS,
    includes = ["include"],
    linkopts = LINKOPTS + [
        "-lncursesw",
        "-lpthread",
        "-ltinfo",
        "-lxmlrpc_server",
        "-lxmlrpc",
        "-lxmlrpc_util",
        "-lxmlrpc_xmlparse",
        "-lxmlrpc_xmltok",
    ],
    deps = [
        "@curl",
        "@libtorrent//:torrent",
    ],
)

cc_binary(
    name = "rtorrent",
    srcs = [
        "src/main.cc",
        "//:included_headers",
    ],
    copts = COPTS,
    features = [
        "fully_static_link",
    ],
    includes = ["include"],
    linkopts = LINKOPTS,
    deps = [
        "//:rtorrent_common",
        "@libtorrent//:torrent",
    ],
)

cc_test(
    name = "rtorrent_test",
    srcs = glob([
        "test/**/*.cc",
    ]) + ["//:included_headers"],
    copts = COPTS,
    includes = ["include"],
    linkopts = LINKOPTS + [
        "-lcppunit",
    ],
    deps = [
        "//:rtorrent_common",
        "@libtorrent//:torrent",
    ],
)
