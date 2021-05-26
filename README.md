# RTorrent BitTorrent Client

rTorrent is a stable, high-performance and low resource consumption BitTorrent client.

This distribution focuses on additional user-facing features, optimizations and better integrations with modern users of RPC interfaces. One of the long-term goal of this project is to switch from antique XML-RPC to modern protocols with bidirectional capabilities such as gRPC, JSON-RPC over WebSocket or GraphQL, which allows real-time events, less serialization/transfer overheads, better security, etc.

There is NO CHANGE in consensus-layer (BitTorrent protocol). As such, this distribution will behave exactly the same as [vanilla rTorrent](https://github.com/rakshasa/rtorrent) in the swarm, and there will not be any compatibility issue with certain trackers, if rTorrent 0.9.8 is supported.

## Getting started

### Installation

Fully static binaries are available at [Releases](https://github.com/jesec/rtorrent/releases).

```sh
# Install rTorrent to /usr/local/bin/rtorrent
# rtorrent-linux-amd64 and rtorrent-linux-arm64 are available
sudo wget https://github.com/jesec/rtorrent/releases/latest/download/rtorrent-linux-amd64 -O /usr/local/bin/rtorrent

# Make it executable
sudo chmod +x /usr/local/bin/rtorrent

# Default configuration
sudo mkdir -p /etc/rtorrent
sudo wget https://github.com/jesec/rtorrent/releases/latest/download/rtorrent.rc -O /etc/rtorrent/rtorrent.rc

# Install as a systemd service (optional)
# This example uses "download" user. Replace it with the an existing user that rTorrent should run with.
sudo wget https://github.com/jesec/rtorrent/releases/latest/download/rtorrent@.service -O /etc/systemd/system/rtorrent@.service
sudo systemctl daemon-reload
sudo systemctl enable rtorrent@download
sudo systemctl start rtorrent@download
```

Or [install with APT repository](https://deb.jesec.io/)

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

It is recommended to expand upon the default configuration if user-specific config files (usually placed to `$HOME/.rtorrent.rc`) are used:

```
## Import default configurations
import = /etc/rtorrent/rtorrent.rc

## Your configurations
...
```

rTorrent tries to load **a** configuration file from several locations:

- $XDG_CONFIG_HOME/rtorrent/rtorrent.rc (highest priority)
- $HOME/.config/rtorrent/rtorrent.rc
- $HOME/.rtorrent.rc
- /etc/rtorrent/rtorrent.rc (lowest priority)

Or, use `-n` argument to prevent rTorrent from loading any configuration file. Then you can use `-o try_import=<path>` to load a config file from an arbitrary location.

## Build

### Bazel

Bazel 3 or later is required.

Bazel manages most dependencies.

Dependencies are specified by the `WORKSPACE` file. Sometimes you may want to override a specific dependency with a local repository for easier development. To do that, use `override_repository` Bazel command line argument. For example, `--override_repository=libtorrent=/path/to/local/libtorrent`.

Unmanaged dependencies:

- GCC/Clang compiler toolchain and C/C++ development files (C++17 support required)

```sh
# Install Bazel
# Use the build of your system and architecture
# bazelisk-linux-arm64 and bazelisk-darwin-amd64 are also available
sudo wget https://github.com/bazelbuild/bazelisk/releases/latest/download/bazelisk-linux-amd64 -O /usr/local/bin/bazel
sudo chmod +x /usr/local/bin/bazel

# Install unmanaged dependencies and build tools
# Use the package manager of your distribution
sudo apt install build-essential

# Clone repository
git clone https://github.com/jesec/rtorrent.git
cd rtorrent

# Build
# By default, the executable is self contained, yet it depends on C/C++ standard libraries of system.
# To generate a fully static executable, use --features=fully_static_link argument.
# Note that glibc have issues that make static executables unreliable.
# If you want fully static, reproducible, portable and stable executable, build with Dockerfile.
bazel build rtorrent

# Binary available at bazel-bin/rtorrent
```

### CMake

CMake 3.5 or later is required.

You have to install dependencies manually to system or let CMake know where to find them.

Dependencies:

- GCC/Clang compiler toolchain and C/C++ development files (C++17 support required)
- [libtorrent](https://github.com/jesec/libtorrent) with development files (core dependency, matching version required)
- libcurl with development files
- libncurses/libncursesw with development files (for terminal UI)
- libxmlrpc-c with development files (optional if USE_XMLRPC=OFF, for XML-RPC support)
- nlohmann/json with development files (optional if USE_JSONRPC=OFF, for JSON-RPC support)
- googletest with development files (optional, for unit tests)

```sh
# Compile and install libtorrent (matching version required)
# Check README of libtorrent for instructions

# Install dependencies and build tools
# Use the package manager of your distribution
sudo apt install build-essential cmake libc6-dev libcurl4-openssl-dev libncursesw5-dev libxmlrpc-c++8-dev libgtest-dev nlohmann-json3-dev

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

To integrate with [Flood](https://flood.js.org), see [discussions](https://github.com/jesec/flood/discussions/120).

## Donate to rTorrent development

[![Donate](https://rakshasa.github.io/rtorrent/donate_paypal_green.svg)](https://paypal.me/jarisundell)

- [Paypal](https://paypal.me/jarisundelljp)
- [Patreon](https://www.patreon.com/rtorrent)
- [SubscribeStar](https://www.subscribestar.com/rtorrent)
- BitCoin: 1MpmXm5AHtdBoDaLZstJw8nupJJaeKu8V8
- Etherium: 0x9AB1e3C3d8a875e870f161b3e9287Db0E6DAfF78
- LiteCoin: LdyaVR67LBnTf6mAT4QJnjSG2Zk67qxmfQ

Help keep rTorrent development going by donating to its creator.
