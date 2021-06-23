load("@rules_foreign_cc//tools/build_defs:configure.bzl", "configure_make")

filegroup(
    name = "all",
    srcs = glob(["**"]),
)

configure_make(
    name = "xmlrpc",
    configure_env_vars = select({
        "@platforms//os:macos": {
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
    lib_source = ":all",
    make_commands = select({
        "@platforms//os:macos": [
            "CFLAGS='-fpic -D_DARWIN_C_SOURCE' make",
            "make install",
        ],
        "//conditions:default": [
            "CFLAGS='-fpic' make",
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
