load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")

config_setting(
    name = "macos",
    values = {"cpu": "darwin"},
    visibility = ["//visibility:private"],
)

config_setting(
    name = "opt",
    values = {"compilation_mode": "opt"},
    visibility = ["//visibility:private"],
)

COPTS = [
    "-std=c++17",
    "-Werror",
    "-Wall",
    "-Wextra",
    "-Wvla",
    "-faligned-new",
] + select({
    "//:opt": [
        "-Ofast",
        "-flto",
    ],
    "//conditions:default": [],
})

LINKOPTS = select({
    "//:opt": [
        "-O3",
        "-flto",
        "-s",
    ],
    "//conditions:default": [],
})

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
        "-lpthread",
        "-lstdc++",
    ] + select({
        "//:macos": [
            "-lxml2",
            "-liconv",
        ],
        "//conditions:default": [
            "-lxmlrpc_server",
            "-lxmlrpc",
            "-lxmlrpc_util",
            "-lxmlrpc_xmlparse",
            "-lxmlrpc_xmltok",
        ],
    }),
    deps = [
        "@curl",
        "@libtorrent//:torrent",
        "@ncurses//:ncursesw",
    ] + select({
        "//:macos": [
            "@xmlrpc",
        ],
        "//conditions:default": [],
    }),
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
    ],
)

cc_binary(
    name = "rtorrent_shared",
    srcs = [
        "src/main.cc",
        "//:included_headers",
    ],
    copts = COPTS,
    includes = ["include"],
    linkopts = LINKOPTS,
    deps = [
        "//:rtorrent_common",
    ],
)

cc_test(
    name = "rtorrent_test",
    srcs = glob([
        "test/**/*.cc",
    ]) + ["//:included_headers"],
    copts = COPTS,
    includes = ["include"],
    linkopts = LINKOPTS + select({
        "//:macos": [],
        "//conditions:default": ["-lcppunit"],
    }),
    deps = [
        "//:rtorrent_common",
    ] + select({
        "//:macos": [
            "@cppunit",
        ],
        "//conditions:default": [],
    }),
)
