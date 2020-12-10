# RTorrent BitTorrent Client

## Introduction

To learn how to use rTorrent visit the [Wiki](https://github.com/rakshasa/rtorrent/wiki).

## Build

```sh
# Clone repository
git clone https://github.com/jesec/rtorrent.git
cd rtorrent

# Install Bazel
# Use the build of your system and architecture
# bazelisk-linux-arm64 and bazelisk-darwin-amd64 are also available
sudo wget https://github.com/bazelbuild/bazelisk/releases/latest/download/bazelisk-linux-amd64 -O /usr/local/bin/bazel
sudo chmod +x /usr/local/bin/bazel

# Install dependencies and build tools
# Use the package manager of your distribution
# Unmanaged dependencies: cmake, compiler toolchain (GCC/Clang) and XMLRPC-C development files
sudo apt install build-essential cmake libc6-dev libxmlrpc-c++8-dev

# Build
bazel build rtorrent

# Binary available at bazel-bin/rtorrent
```

## Docker

[Dockerfile](https://github.com/jesec/rtorrent/blob/master/Dockerfile)

To test: `docker run -it jesec/rtorrent`

Note that you have to expose BitTorrent port (e.g. `-p 50000:50000`) and map folders (e.g. `-v /home/download:/home/download`) yourself.

By default, rTorrent's files are located in `/home/download/.local/share/rtorrent`. Check [doc/rtorrent.rc](https://github.com/jesec/rtorrent/blob/master/doc/rtorrent.rc) to know more about the default configurations.

You can execute rTorrent [commands](https://rtorrent-docs.readthedocs.io/en/latest/cmd-ref.html) at start to set port, set announced IP, etc.

For example, to launch rTorrent with port `6881` and DHT disabled, `docker run -it jesec/rtorrent -o network.port_range.set=6881-6881,dht.mode.set=disable`.

To integrate with [Flood](https://flood.js.org), see [flood:Dockerfile.rtorrent](https://github.com/jesec/flood/blob/master/Dockerfile.rtorrent).

## Donate to rTorrent development

[![Donate](https://rakshasa.github.io/rtorrent/donate_paypal_green.svg)](https://paypal.me/jarisundell)

- [Paypal](https://paypal.me/jarisundelljp)
- [Patreon](https://www.patreon.com/rtorrent)
- [SubscribeStar](https://www.subscribestar.com/rtorrent)
- BitCoin: 1MpmXm5AHtdBoDaLZstJw8nupJJaeKu8V8
- Etherium: 0x9AB1e3C3d8a875e870f161b3e9287Db0E6DAfF78
- LiteCoin: LdyaVR67LBnTf6mAT4QJnjSG2Zk67qxmfQ

Help keep rTorrent development going by donating to its creator.
