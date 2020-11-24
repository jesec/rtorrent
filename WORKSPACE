load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

git_repository(
    name = "libtorrent",
    branch = "master",
    remote = "https://github.com/jesec/libtorrent.git",
)

load("@libtorrent//:libtorrent_deps.bzl", "libtorrent_deps")

libtorrent_deps()
