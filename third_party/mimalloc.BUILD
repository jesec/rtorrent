load("@rules_foreign_cc//tools/build_defs:cmake.bzl", "cmake_external")

filegroup(
    name = "all",
    srcs = glob(["**"]),
)

cmake_external(
    name = "_mimalloc",
    binaries = ["mimalloc.o"],
    cache_entries = {
        "CMAKE_BUILD_TYPE": "Release",
        "CMAKE_INSTALL_LIBDIR": "lib",
        "CMAKE_POSITION_INDEPENDENT_CODE": "on",
        "MI_OVERRIDE": "on",
        "MI_BUILD_STATIC": "off",
        "MI_BUILD_SHARED": "off",
        "MI_BUILD_OBJECT": "on",
        "MI_BUILD_TESTS": "off",
        "MI_INSTALL_TOPLEVEL": "on",
    },
    lib_source = "//:all",
    out_bin_dir = "lib",
)

filegroup(
    name = "mimalloc",
    srcs = [":_mimalloc"],
    output_group = "mimalloc.o",
    visibility = ["//visibility:public"],
)
