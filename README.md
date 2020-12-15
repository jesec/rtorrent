# RTorrent BitTorrent Client

rTorrent is a stable, high-performance and low resource consumption BitTorrent client.

## Getting started

### Installation

Fully static binaries are available at [Github Actions](https://github.com/jesec/rtorrent/actions?query=workflow%3A%22Publish+rolling+build%22).

- Extract, `sudo cp rtorrent /usr/local/bin/rtorrent` and `sudo chmod +x /usr/local/bin/rtorrent`
- Download default configuration from [doc/rtorrent.rc](https://github.com/jesec/rtorrent/raw/master/doc/rtorrent.rc) and copy it to `/etc/rtorrent/rtorrent.rc` or `$HOME/.rtorrent.rc`.

Or [run with Docker](https://github.com/jesec/rtorrent#docker)

Or [build from source](https://github.com/jesec/rtorrent#build)

### Use

Run `rtorrent`

You can execute rTorrent [commands](https://rtorrent-docs.readthedocs.io/en/latest/cmd-ref.html) to set port, set announced IP, etc.

For example, to launch rTorrent with port `6881` and DHT disabled, `rtorrent -o network.port_range.set=6881-6881,dht.mode.set=disable`.

Checkout [Flood](https://flood.js.org), a modern Web UI for rTorrent.

To learn how to use rTorrent visit the [Wiki](https://github.com/rakshasa/rtorrent/wiki).

### Configuration

Default configuration file is available at [doc/rtorrent.rc](https://github.com/jesec/rtorrent/blob/master/doc/rtorrent.rc). It is often installed to `/etc/rtorrent/rtorrent.rc`.

You may modify the configuration file to fit your needs. Alternatively, use `-o`, as documented above, to override some configurations but keep using the loaded configuration file.

rTorrent loads **a** configuration file from several locations:

- $XDG_CONFIG_HOME/rtorrent/rtorrent.rc (highest priority)
- $HOME/.config/rtorrent/rtorrent.rc
- $HOME/.rtorrent.rc
- /etc/rtorrent/rtorrent.rc (lowest priority)

Or, use `-n` argument to prevent rTorrent from loading any configuration file. Then you can use `-o try_import=<path>` to load a config file from an arbitrary location.

## Build

### Bazel

Bazel 3 or later is required.

Bazel manages most dependencies.

Unmanaged dependencies:

- GCC/Clang compiler toolchain and C/C++ development files (C++17 support required)
- cmake (for build info generation)
- libxmlrpc-c with development files (for XMLRPC support)
- libcppunit with development files (optional, for unit tests)

```sh
# Install Bazel
# Use the build of your system and architecture
# bazelisk-linux-arm64 and bazelisk-darwin-amd64 are also available
sudo wget https://github.com/bazelbuild/bazelisk/releases/latest/download/bazelisk-linux-amd64 -O /usr/local/bin/bazel
sudo chmod +x /usr/local/bin/bazel

# Install unmanaged dependencies and build tools
# Use the package manager of your distribution
sudo apt install build-essential cmake libc6-dev libxmlrpc-c++8-dev

# Clone repository
git clone https://github.com/jesec/rtorrent.git
cd rtorrent

# Build
# To generate a fully static executable, use rtorrent.
# To generate a shared executable, use rtorrent-shared.
# Note that certain versions of glibc have bugs that make static executables unreliable.
# If you do want fully static, reproducible, portable and stable executable, build with Dockerfile.
bazel build rtorrent

# Binary available at bazel-bin/rtorrent (or bazel-bin/rtorrent-shared)
```

### CMake

CMake 3.5 or later is required.

You have to install dependencies manually to system or let CMake know where to find them.

Dependencies:

- GCC/Clang compiler toolchain and C/C++ development files (C++17 support required)
- libtorrent with development files (core dependency, matching version required)
- libcurl with development files
- libncurses/libncursesw with development files (for terminal UI)
- libxmlrpc-c with development files (optional if USE_XMLRPC=OFF, for XMLRPC support)
- libcppunit with development files (optional, for unit tests)

```sh
# Compile and install libtorrent (matching version required)
# Check README of libtorrent for instructions

# Install dependencies and build tools
# Use the package manager of your distribution
sudo apt install build-essential cmake libc6-dev libcurl4-openssl-dev libncursesw5-dev libxmlrpc-c++8-dev libcppunit-dev

# Clone repository
git clone https://github.com/jesec/rtorrent.git
cd rtorrent

# Configure and generate Makefile
cmake .

# Build
# By default, shared binaries are generated
make

# Binary available at ./rtorrent

# Install (optional)
sudo make install
```

## Docker

[Dockerfile](https://github.com/jesec/rtorrent/blob/master/Dockerfile)

To test: `docker run -it jesec/rtorrent`

Note that you have to expose BitTorrent port (e.g. `-p 50000:50000`) and map folders (e.g. `-v /home/download:/home/download`) yourself.

By default, rTorrent's files are located in `$HOME/.local/share/rtorrent`. Check [doc/rtorrent.rc](https://github.com/jesec/rtorrent/blob/master/doc/rtorrent.rc) to know more about the default configurations.

To integrate with [Flood](https://flood.js.org), see [flood:Dockerfile.rtorrent](https://github.com/jesec/flood/blob/master/Dockerfile.rtorrent) and [discussions](https://github.com/jesec/flood/discussions/120).

## Donate to rTorrent development

[![Donate](https://rakshasa.github.io/rtorrent/donate_paypal_green.svg)](https://paypal.me/jarisundell)

- [Paypal](https://paypal.me/jarisundelljp)
- [Patreon](https://www.patreon.com/rtorrent)
- [SubscribeStar](https://www.subscribestar.com/rtorrent)
- BitCoin: 1MpmXm5AHtdBoDaLZstJw8nupJJaeKu8V8
- Etherium: 0x9AB1e3C3d8a875e870f161b3e9287Db0E6DAfF78
- LiteCoin: LdyaVR67LBnTf6mAT4QJnjSG2Zk67qxmfQ

Help keep rTorrent development going by donating to its creator.
