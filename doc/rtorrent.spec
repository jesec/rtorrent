Name:          rtorrent
License:       GPLv2+ with exceptions
Version:       0.9.8
Release:       100master.jc
Summary:       a stable and high-performance BitTorrent client
URL:           https://github.com/jesec/rtorrent

%description
a stable and high-performance BitTorrent client

%build
tar xf bazel-out/*/bin/rtorrent-pkg-data.tar.gz

%install
rm -rf %{buildroot}

mkdir -p %{buildroot}%{_bindir}/
install -m 755 ./usr/bin/rtorrent %{buildroot}%{_bindir}/rtorrent

cp -rf ./etc %{buildroot}/

%clean
rm -rf %{buildroot}

%files
%attr(0755, root, root) %{_bindir}/rtorrent
%attr(0644, root, root) /etc/systemd/system/rtorrent@.service
%attr(0644, root, root) /etc/rtorrent/rtorrent.rc
