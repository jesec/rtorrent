load("@rules_foreign_cc//foreign_cc:defs.bzl", "configure_make")

filegroup(
    name = "all",
    srcs = glob(["**"]),
)

configure_make(
    name = "xmlrpc",
    configure_in_place = True,
    configure_options = [
        "--disable-wininet-client",
        "--disable-curl-client",
        "--disable-libwww-client",
        "--disable-abyss-server",
        "--disable-cgi-server",
        "--disable-cplusplus",
    ],
    env = select({
        "@platforms//os:macos": {
            "AR": "",
        },
        "//conditions:default": {},
    }),
    lib_source = ":all",
    out_static_libs = [
        "libxmlrpc_server.a",
        "libxmlrpc.a",
        "libxmlrpc_xmlparse.a",
        "libxmlrpc_xmltok.a",
        "libxmlrpc_util.a",
    ],
    tool_prefix = select({
        "@platforms//os:macos": "CFLAGS='-fpic -D_DARWIN_C_SOURCE'",
        "//conditions:default": "CFLAGS='-fpic'",
    }),
    visibility = ["//visibility:public"],
)
