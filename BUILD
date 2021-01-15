load("@bazel_skylib//lib:selects.bzl", "selects")
load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")
load("@rules_foreign_cc//tools/build_defs:configure.bzl", "configure_make")

config_setting(
    name = "macos_x86_64",
    values = {
        "apple_platform_type": "macos",
        "cpu": "darwin",
    },
    visibility = ["//visibility:private"],
)

config_setting(
    name = "macos_arm64",
    values = {
        "apple_platform_type": "macos",
        "cpu": "darwin_arm64",
    },
    visibility = ["//visibility:private"],
)

selects.config_setting_group(
    name = "macos",
    match_any = [
        ":macos_x86_64",
        ":macos_arm64",
    ],
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

configure_make(
    name = "xmlrpc",
    configure_env_vars = select({
        "//:macos": {
            "AR": "",
        },
        "//conditions:default": {},
    }),
    configure_in_place = True,
    configure_options = [
        "--disable-wininet-client",
        "--disable-curl-client",
        "--disable-libwww-client",
        "--disable-abyss-server",
        "--disable-cgi-server",
        "--disable-cplusplus",
    ],
    lib_source = "@xmlrpc//:all",
    make_commands = select({
        "//:macos": [
            "CFLAGS='-D_DARWIN_C_SOURCE' make",
            "make install",
        ],
        "//conditions:default": [
            "make",
            "make install",
        ],
    }),
    static_libraries = [
        "libxmlrpc_server.a",
        "libxmlrpc.a",
        "libxmlrpc_xmlparse.a",
        "libxmlrpc_xmltok.a",
        "libxmlrpc_util.a",
    ],
    visibility = ["//visibility:public"],
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
            "-lncurses",
        ],
        "//conditions:default": [],
    }),
    deps = [
        "@curl",
        "xmlrpc",
        "@libtorrent//:torrent",
    ] + select({
        "//:macos": [],
        "//conditions:default": [
            "@ncurses//:ncursesw",
        ],
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
