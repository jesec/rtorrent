# Copied from https://github.com/grpc/grpc/tree/master/third_party/cares

load("@bazel_skylib//rules:copy_file.bzl", "copy_file")
load("@bazel_skylib//lib:selects.bzl", "selects")
load("@rules_cc//cc:defs.bzl", "cc_library")

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

config_setting(
    name = "windows",
    values = {"cpu": "x64_windows"},
    visibility = ["//visibility:private"],
)

# Android is not officially supported through C++.
# This just helps with the build for now.
config_setting(
    name = "android",
    values = {
        "crosstool_top": "//external:android/crosstool",
    },
    visibility = ["//visibility:private"],
)

# iOS is not officially supported through C++.
# This just helps with the build for now.
config_setting(
    name = "ios_x86_64",
    values = {"cpu": "ios_x86_64"},
    visibility = ["//visibility:private"],
)

config_setting(
    name = "ios_armv7",
    values = {"cpu": "ios_armv7"},
    visibility = ["//visibility:private"],
)

config_setting(
    name = "ios_armv7s",
    values = {"cpu": "ios_armv7s"},
    visibility = ["//visibility:private"],
)

config_setting(
    name = "ios_arm64",
    values = {"cpu": "ios_arm64"},
    visibility = ["//visibility:private"],
)

# The following architectures are found in
# https://github.com/bazelbuild/bazel/blob/master/src/main/java/com/google/devtools/build/lib/rules/apple/ApplePlatform.java
config_setting(
    name = "tvos_x86_64",
    values = {"cpu": "tvos_x86_64"},
    visibility = ["//visibility:private"],
)

config_setting(
    name = "tvos_arm64",
    values = {"cpu": "tvos_arm64"},
    visibility = ["//visibility:private"],
)

config_setting(
    name = "watchos_i386",
    values = {"cpu": "watchos_i386"},
    visibility = ["//visibility:private"],
)

config_setting(
    name = "watchos_x86_64",
    values = {"cpu": "watchos_x86_64"},
    visibility = ["//visibility:private"],
)

config_setting(
    name = "watchos_armv7k",
    values = {"cpu": "watchos_armv7k"},
    visibility = ["//visibility:private"],
)

config_setting(
    name = "watchos_arm64_32",
    values = {"cpu": "watchos_arm64_32"},
    visibility = ["//visibility:private"],
)

selects.config_setting_group(
    name = "darwin",
    match_any = [
        ":macos_x86_64",
        ":macos_arm64",
        ":ios_x86_64",
        ":ios_armv7",
        ":ios_armv7s",
        ":ios_arm64",
        ":tvos_x86_64",
        ":tvos_arm64",
        ":watchos_i386",
        ":watchos_x86_64",
        ":watchos_armv7k",
        ":watchos_arm64_32",
    ],
)

copy_file(
    name = "ares_build_h",
    src = "@rtorrent//third_party/cares:ares_build.h",
    out = "ares_build.h",
)

copy_file(
    name = "ares_config_h",
    src = select({
        ":darwin": "@rtorrent//third_party/cares:config_darwin/ares_config.h",
        ":windows": "@rtorrent//third_party/cares:config_windows/ares_config.h",
        ":android": "@rtorrent//third_party/cares:config_android/ares_config.h",
        "//conditions:default": "@rtorrent//third_party/cares:config_linux/ares_config.h",
    }),
    out = "ares_config.h",
)

cc_library(
    name = "ares",
    srcs = [
        "ares__close_sockets.c",
        "ares__get_hostent.c",
        "ares__read_line.c",
        "ares__timeval.c",
        "ares_android.c",
        "ares_cancel.c",
        "ares_create_query.c",
        "ares_data.c",
        "ares_destroy.c",
        "ares_expand_name.c",
        "ares_expand_string.c",
        "ares_fds.c",
        "ares_free_hostent.c",
        "ares_free_string.c",
        "ares_getenv.c",
        "ares_gethostbyaddr.c",
        "ares_gethostbyname.c",
        "ares_getnameinfo.c",
        "ares_getopt.c",
        "ares_getsock.c",
        "ares_init.c",
        "ares_library_init.c",
        "ares_llist.c",
        "ares_mkquery.c",
        "ares_nowarn.c",
        "ares_options.c",
        "ares_parse_a_reply.c",
        "ares_parse_aaaa_reply.c",
        "ares_parse_mx_reply.c",
        "ares_parse_naptr_reply.c",
        "ares_parse_ns_reply.c",
        "ares_parse_ptr_reply.c",
        "ares_parse_soa_reply.c",
        "ares_parse_srv_reply.c",
        "ares_parse_txt_reply.c",
        "ares_platform.c",
        "ares_process.c",
        "ares_query.c",
        "ares_search.c",
        "ares_send.c",
        "ares_strcasecmp.c",
        "ares_strdup.c",
        "ares_strerror.c",
        "ares_strsplit.c",
        "ares_timeout.c",
        "ares_version.c",
        "ares_writev.c",
        "bitncmp.c",
        "inet_net_pton.c",
        "inet_ntop.c",
        "windows_port.c",
    ],
    hdrs = [
        "ares.h",
        "ares_android.h",
        "ares_build.h",
        "ares_config.h",
        "ares_data.h",
        "ares_dns.h",
        "ares_getenv.h",
        "ares_getopt.h",
        "ares_inet_net_pton.h",
        "ares_iphlpapi.h",
        "ares_ipv6.h",
        "ares_library_init.h",
        "ares_llist.h",
        "ares_nowarn.h",
        "ares_platform.h",
        "ares_private.h",
        "ares_rules.h",
        "ares_setup.h",
        "ares_strcasecmp.h",
        "ares_strdup.h",
        "ares_strsplit.h",
        "ares_version.h",
        "ares_writev.h",
        "bitncmp.h",
        "config-win32.h",
        "nameser.h",
        "setup_once.h",
    ],
    copts = [
        "-D_GNU_SOURCE",
        "-D_HAS_EXCEPTIONS=0",
        "-DHAVE_CONFIG_H",
    ] + select({
        ":windows": [
            "-DNOMINMAX",
            "-D_CRT_SECURE_NO_DEPRECATE",
            "-D_CRT_NONSTDC_NO_DEPRECATE",
            "-D_WIN32_WINNT=0x0600",
        ],
        "//conditions:default": [],
    }),
    defines = ["CARES_STATICLIB"],
    includes = ["."],
    linkopts = select({
        ":windows": ["-defaultlib:ws2_32.lib"],
        "//conditions:default": [],
    }),
    linkstatic = 1,
    visibility = [
        "//visibility:public",
    ],
    alwayslink = 1,
)
