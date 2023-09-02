load("@rules_foreign_cc//foreign_cc:defs.bzl", "configure_make")

filegroup(
    name = "all",
    srcs = glob(
      ["**"]
    ),
)

configure_make(
   name="nghttp2",
   lib_source="//:all",
   visibility = ["//visibility:public"],
   configure_options = ["--enable-lib-only"],
   out_bin_dir = "lib/.libs",
   out_static_libs = ["libnghttp2.a"],
   env = {
     "CC":"clang",
     "CXX":"clang++",
     "CXXFLAGS": "-std=c++17"
   },
)
