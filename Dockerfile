ARG ALPINE_IMAGE=alpine

FROM ${ALPINE_IMAGE} as build

WORKDIR /root/rtorrent

# Install build dependencies
RUN apk --no-cache add \
    build-base \
    cmake \
    coreutils \
    git \
    linux-headers \
    python2 \
    python3

# Install Bazel 3 from edge testing repository
RUN apk --no-cache add \
    bazel3 \
    --repository=http://dl-cdn.alpinelinux.org/alpine/edge/testing

# Checkout rTorrent sources from current directory
COPY . ./

# # Checkout rTorrent sources from Github repository
# RUN git clone https://github.com/jesec/rtorrent .

# Build rTorrent packages
RUN bazel build rtorrent-deb --features=fully_static_link --verbose_failures

# Copy outputs
RUN mkdir dist
RUN cp -L bazel-bin/rtorrent dist/
RUN cp -L bazel-bin/rtorrent-deb.deb dist/

# Now get the clean image
FROM ${ALPINE_IMAGE} as rtorrent

# Install rTorrent built
COPY --from=build /root/rtorrent/dist/rtorrent /usr/local/bin

# Install runtime dependencies
RUN apk --no-cache add \
    ca-certificates \
    ncurses-terminfo-base

# Copy default configuration file to /etc/rtorrent
COPY --from=build /root/rtorrent/doc/rtorrent.rc /etc/rtorrent/

# Create "download" user
RUN adduser -h /home/download -s /sbin/nologin --disabled-password --uid 1001 download

# Run as "download" user
USER download

# rTorrent
ENTRYPOINT ["rtorrent"]
