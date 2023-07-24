workspace(name = "rtorrent")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "libtorrent",
    sha256 = "57422c8bbf402bc0669b008f4ddaf1674cc7d5b4a9f6e5aa1e237b99eed840b4",
    strip_prefix = "libtorrent-3a87f4acfcdd6c153dd4eaccca97870489b53885",
    url = "https://github.com/jesec/libtorrent/archive/3a87f4acfcdd6c153dd4eaccca97870489b53885.zip",
)

load("@libtorrent//:libtorrent_repos.bzl", "libtorrent_repos")

libtorrent_repos()

load("@libtorrent//:libtorrent_deps.bzl", "libtorrent_deps")

libtorrent_deps()

http_archive(
    name = "bazel_skylib",
    sha256 = "f7be3474d42aae265405a592bb7da8e171919d74c16f082a5457840f06054728",
    urls = [
        "https://github.com/bazelbuild/bazel-skylib/releases/download/1.2.1/bazel-skylib-1.2.1.tar.gz",
        "https://mirror.bazel.build/github.com/bazelbuild/bazel-skylib/releases/download/1.2.1/bazel-skylib-1.2.1.tar.gz",
    ],
)

load("@bazel_skylib//:workspace.bzl", "bazel_skylib_workspace")

bazel_skylib_workspace()

http_archive(
    name = "rules_pkg",
    sha256 = "8a298e832762eda1830597d64fe7db58178aa84cd5926d76d5b744d6558941c2",
    urls = [
        "https://mirror.bazel.build/github.com/bazelbuild/rules_pkg/releases/download/0.7.0/rules_pkg-0.7.0.tar.gz",
        "https://github.com/bazelbuild/rules_pkg/releases/download/0.7.0/rules_pkg-0.7.0.tar.gz",
    ],
)

load("@rules_pkg//:deps.bzl", "rules_pkg_dependencies")

rules_pkg_dependencies()

load("@rules_pkg//toolchains/rpm:rpmbuild_configure.bzl", "find_system_rpmbuild")

find_system_rpmbuild(name = "rules_pkg_rpmbuild")

http_archive(
    name = "cares",
    build_file = "@rtorrent//:third_party/cares.BUILD",
    sha256 = "4803c844ce20ce510ef0eb83f8ea41fa24ecaae9d280c468c582d2bb25b3913d",
    strip_prefix = "c-ares-1.17.2",
    urls = [
        "https://github.com/c-ares/c-ares/releases/download/cares-1_17_2/c-ares-1.17.2.tar.gz",
        "https://c-ares.haxx.se/download/c-ares-1.17.2.tar.gz",
    ],
)

http_archive(
    name = "curl",
    build_file = "@rtorrent//:third_party/curl.BUILD",
    sha256 = "b0a3428acb60fa59044c4d0baae4e4fc09ae9af1d8a3aa84b2e3fbcd99841f77",
    strip_prefix = "curl-7.77.0",
    urls = [
        "https://github.com/curl/curl/releases/download/curl-7_77_0/curl-7.77.0.tar.gz",
        "https://curl.haxx.se/download/curl-7.77.0.tar.gz",
    ],
)

http_archive(
    name = "json",
    build_file = "@rtorrent//:third_party/json.BUILD",
    sha256 = "b94997df68856753b72f0d7a3703b7d484d4745c567f3584ef97c96c25a5798e",
    urls = ["https://github.com/nlohmann/json/releases/download/v3.10.5/include.zip"],
)

http_archive(
    name = "ncurses",
    build_file = "@rtorrent//:third_party/ncurses.BUILD",
    sha256 = "30306e0c76e0f9f1f0de987cf1c82a5c21e1ce6568b9227f7da5b71cbea86c9d",
    strip_prefix = "ncurses-6.2",
    urls = ["https://ftp.gnu.org/gnu/ncurses/ncurses-6.2.tar.gz"],
)

http_archive(
    name = "com_google_absl",
    sha256 = "59b862f50e710277f8ede96f083a5bb8d7c9595376146838b9580be90374ee1f",
    strip_prefix = "abseil-cpp-20210324.2",
    urls = ["https://github.com/abseil/abseil-cpp/archive/refs/tags/20210324.2.tar.gz"],
)

http_archive(
    name = "com_google_googletest",
    sha256 = "b4870bf121ff7795ba20d20bcdd8627b8e088f2d1dab299a031c1034eddc93d5",
    strip_prefix = "googletest-release-1.11.0",
    urls = ["https://github.com/google/googletest/archive/refs/tags/release-1.11.0.tar.gz"],
)

# Foreign CC dependencies
http_archive(
    name = "mimalloc",
    build_file = "@rtorrent//:third_party/mimalloc.BUILD",
    sha256 = "23e7443d0b4d7aa945779ea8a806e4e109c0ed62d740953d3656cddea7e04cf8",
    strip_prefix = "mimalloc-2.0.6",
    urls = ["https://github.com/microsoft/mimalloc/archive/refs/tags/v2.0.6.zip"],
)
