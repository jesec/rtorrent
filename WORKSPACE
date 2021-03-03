workspace(name = "rtorrent")

load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

git_repository(
    name = "libtorrent",
    branch = "master",
    remote = "https://github.com/jesec/libtorrent.git",
)

load("@libtorrent//:libtorrent_repos.bzl", "libtorrent_repos")

libtorrent_repos()

load("@libtorrent//:libtorrent_deps.bzl", "libtorrent_deps")

libtorrent_deps()

http_archive(
    name = "bazel_skylib",
    sha256 = "1c531376ac7e5a180e0237938a2536de0c54d93f5c278634818e0efc952dd56c",
    urls = [
        "https://github.com/bazelbuild/bazel-skylib/releases/download/1.0.3/bazel-skylib-1.0.3.tar.gz",
        "https://mirror.bazel.build/github.com/bazelbuild/bazel-skylib/releases/download/1.0.3/bazel-skylib-1.0.3.tar.gz",
    ],
)

load("@bazel_skylib//:workspace.bzl", "bazel_skylib_workspace")

bazel_skylib_workspace()

http_archive(
    name = "rules_pkg",
    sha256 = "6b5969a7acd7b60c02f816773b06fcf32fbe8ba0c7919ccdc2df4f8fb923804a",
    url = "https://github.com/bazelbuild/rules_pkg/releases/download/0.3.0/rules_pkg-0.3.0.tar.gz",
)

load("@rules_pkg//:deps.bzl", "rules_pkg_dependencies")

rules_pkg_dependencies()

http_archive(
    name = "cares",
    build_file = "@rtorrent//:third_party/cares/cares.BUILD",
    sha256 = "6cdb97871f2930530c97deb7cf5c8fa4be5a0b02c7cea6e7c7667672a39d6852",
    strip_prefix = "c-ares-1.15.0",
    urls = [
        "https://github.com/c-ares/c-ares/releases/download/cares-1_15_0/c-ares-1.15.0.tar.gz",
    ],
)

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

http_archive(
    name = "json",
    build_file = "@rtorrent//:third_party/json.BUILD",
    sha256 = "6bea5877b1541d353bd77bdfbdb2696333ae5ed8f9e8cc22df657192218cad91",
    urls = [
        "https://github.com/nlohmann/json/releases/download/v3.9.1/include.zip",
    ],
)

http_archive(
    name = "ncurses",
    build_file = "@rtorrent//:third_party/ncurses.BUILD",
    sha256 = "30306e0c76e0f9f1f0de987cf1c82a5c21e1ce6568b9227f7da5b71cbea86c9d",
    strip_prefix = "ncurses-6.2",
    urls = [
        "https://ftp.gnu.org/gnu/ncurses/ncurses-6.2.tar.gz",
        "https://invisible-mirror.net/archives/ncurses/ncurses-6.2.tar.gz",
    ],
)

http_archive(
    name = "com_google_absl",
    sha256 = "00c3707bf9cd5eabd1ec6932cc65b97378c043f22573be3adf7d11bb7af17d06",
    strip_prefix = "abseil-cpp-f3f785ab59478dd0312bf1b5df65d380650bf0dc",
    urls = ["https://github.com/abseil/abseil-cpp/archive/f3f785ab59478dd0312bf1b5df65d380650bf0dc.zip"],
)

http_archive(
    name = "com_google_googletest",
    sha256 = "3519a051b20f0dd3a58e1dedd391a3cbd27eb70189afb1185dc4eaefe111211f",
    strip_prefix = "googletest-1de637fbdd4ab0051229707f855eee76f5a3d5da",
    urls = ["https://github.com/google/googletest/archive/1de637fbdd4ab0051229707f855eee76f5a3d5da.zip"],
)

# Foreign CC dependencies
all_content = """filegroup(name = "all", srcs = glob(["**"]), visibility = ["//visibility:public"])"""

http_archive(
    name = "xmlrpc",
    build_file_content = all_content,
    patches = ["@rtorrent//:third_party/xmlrpc.patch"],
    sha256 = "93d81a32f4ecfeb914c05f77476ba0af2e6b93ef6673fafdc12878f71d70a276",
    strip_prefix = "xmlrpc-c-146e9bf7f8933c3baec871dfc2365e471171ddf4/advanced",
    urls = ["https://github.com/mirror/xmlrpc-c/archive/146e9bf7f8933c3baec871dfc2365e471171ddf4.zip"],
)
