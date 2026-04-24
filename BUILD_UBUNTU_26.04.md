# Ubuntu 26.04 Build Guide

This guide provides step-by-step instructions for building radiotray-lite on Ubuntu 26.04 (Noble Numbat).

## System Requirements

- Ubuntu 26.04 (or compatible Debian/Ubuntu derivatives)
- 2GB RAM minimum
- 500MB free disk space

## Installation Steps

### 1. Install Build Dependencies

```bash
sudo apt-get update
sudo apt-get install -y build-essential cmake pkg-config \
  libgtkmm-3.0-dev \
  libgstreamermm-1.0-dev \
  libcurl4-openssl-dev \
  libnotify-dev \
  libayatana-appindicator3-dev \
  libmagic-dev \
  git
```

### 2. Clone the Repository

```bash
git clone https://github.com/betooliveirame/radiotray-lite.git
cd radiotray-lite
```

### 3. Build the Project

```bash
mkdir -p build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr
make -j$(nproc)
```

### 4. Create Debian Package

```bash
cpack -G DEB
```

The `.deb` package will be created in `build/packages/radiotray-lite-0.2.20-Linux.deb`

### 5. Install the Package

```bash
sudo dpkg -i packages/radiotray-lite-*.deb
```

## Troubleshooting

### CMake not finding dependencies

If CMake fails to find dependencies, ensure all `-dev` packages are installed:

```bash
pkg-config --list-all | grep -E "(gtkmm|gstreamer|curl|notify|appindicator|magic)"
```

### Build errors with newer GCC

If you encounter compilation warnings as errors, verify your GCC version:

```bash
gcc --version
```

Ubuntu 26.04 ships with GCC 13+, which has stricter warnings. The build should handle these correctly.

### GStreamer plugin issues at runtime

If playback fails, ensure GStreamer plugins are installed:

```bash
sudo apt-get install gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-plugins-ugly
```

## Verifying Installation

After installation, launch the application:

```bash
radiotray-lite
```

The application should appear in your system tray. You can verify the version:

```bash
radiotray-lite --version
# or check the binary
file /usr/bin/radiotray-lite
```

## Building from Source (Without Package)

If you prefer direct installation without creating a package:

```bash
mkdir -p build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr
make -j$(nproc)
sudo make install
```

## Configuration

After first run, configuration files are created at:
- `~/.config/radiotray-lite/config.xml`
- `~/.config/radiotray-lite/bookmarks.xml`

To import bookmarks from the original Radio Tray:

```bash
mkdir -p ~/.config/radiotray-lite/
cp ~/.local/share/radiotray/bookmarks.xml ~/.config/radiotray-lite/
```

## Uninstallation

To remove the package:

```bash
sudo apt-get remove radiotray-lite
```

Or if built from source:

```bash
sudo make -C build uninstall
```
