ARG ALPINE_IMAGE=alpine

FROM ${ALPINE_IMAGE} as build

WORKDIR /root/rtorrent

# Install build dependencies
RUN apk --no-cache add \
    bash \
    build-base \
    coreutils \
    gcompat \
    git \
    linux-headers \
    python2 \
    python3

# Install Bazel
RUN apk --allow-untrusted --no-cache add \
    bazel \
    -Xhttps://dl-cdn.alpinelinux.org/alpine/edge/testing \
    -Xhttps://github.com/jesec/bazel-alpine/raw/repo

# Checkout rTorrent sources from current directory
COPY . ./

# # Checkout rTorrent sources from Github repository
# RUN git clone https://github.com/jesec/rtorrent .

# Set architecture for .deb package
RUN if [[ `uname -m` == "aarch64" ]]; \
    then sed -i 's/architecture = \"all\"/architecture = \"arm64\"/' BUILD.bazel; \
    elif [[ `uname -m` == "x86_64" ]]; \
    then sed -i 's/architecture = \"all\"/architecture = \"amd64\"/' BUILD.bazel; \
    fi

# Build rTorrent packages
RUN bazel build rtorrent-deb --features=fully_static_link --verbose_failures

# Copy outputs
RUN mkdir dist
RUN cp -L bazel-bin/rtorrent dist/
RUN cp -L bazel-bin/rtorrent-deb.deb dist/

# Now get the clean image
FROM ${ALPINE_IMAGE} as build-sysroot

WORKDIR /root

# Fetch runtime dependencies
RUN apk --no-cache add \
    binutils \
    ca-certificates \
    ncurses-terminfo-base

# Install rTorrent and dependencies to new system root
RUN mkdir -p /root/sysroot/etc/ssl/certs
COPY --from=build /root/rtorrent/dist/rtorrent-deb.deb .
RUN ar -xv rtorrent-deb.deb
RUN tar xvf data.tar.* -C /root/sysroot/
RUN cp -L /etc/ssl/certs/ca-certificates.crt /root/sysroot/etc/ssl/certs/ca-certificates.crt
RUN cp -r /etc/terminfo /root/sysroot/etc/terminfo

# Create 1001:1001 user
RUN mkdir -p /root/sysroot/home/download
RUN chown 1001:1001 /root/sysroot/home/download

FROM scratch as rtorrent

COPY --from=build-sysroot /root/sysroot /

# Run as 1001:1001 user
ENV HOME=/home/download
USER 1001:1001

# rTorrent
ENTRYPOINT ["rtorrent"]
