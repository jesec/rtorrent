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
