# RTorrent BitTorrent Client

## Introduction

To learn how to use rTorrent visit the [Wiki](https://github.com/rakshasa/rtorrent/wiki).

## Build

```sh
# Clone repository
git clone https://github.com/jesec/rtorrent.git
cd rtorrent

# Install Bazel
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

To test: `docker run -it --user root:root jesec/rtorrent`

Note that you have to explicitly configure and specify user.

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
