### About
`radiotray-lite` is a lightweight clone of the original [Radio Tray](http://radiotray.sourceforge.net/) online radio streaming player rewritten in C++.

![Screenshot](images/radiotray-lite.png)

### Key features
* Runs on a Linux system tray.
* Has minimum interface possible.
* Plays most media formats (it uses gstreamer).
* Supports PLS, M3U, ASX, RAM, XSPF playlists.

### Build

#### Ubuntu/Debian Dependencies

Install required development packages:

**Ubuntu 26.04 (Noble) and later:**
```bash
sudo apt-get install build-essential cmake pkg-config \
  libgtkmm-3.0-dev \
  libgstreamermm-1.0-dev \
  libcurl4-openssl-dev \
  libnotify-dev \
  libayatana-appindicator3-dev \
  libmagic-dev
```

**Ubuntu 22.04 (Jammy) and Ubuntu 20.04 (Focal):**
```bash
sudo apt-get install build-essential cmake pkg-config \
  libgtkmm-3.0-dev \
  libgstreamermm-1.0-dev \
  libcurl4-openssl-dev \
  libnotify-dev \
  libappindicator3-dev \
  libmagic-dev
```

**Older versions (Ubuntu 16.04, 18.04):**
May require either `libgstreamermm-0.10-dev` or `libgstreamermm-1.0-dev` depending on availability.

#### Build Instructions

```bash
mkdir -p build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr
make -j$(nproc)
sudo cpack -G DEB
# or for RPM: cpack -G RPM
sudo dpkg -i packages/*.deb
```

The package will be created in the `build/packages/` directory.

#### Alternative: Direct Installation
```bash
mkdir -p build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr
make -j$(nproc)
sudo make install
```

### Configuration
#### Bookmarks
Copy your existing `bookmarks.xml` from [Radio Tray](http://radiotray.sourceforge.net/) (which is usually located at
`$HOME/.local/share/radiotray/bookmarks.xml`) into `$HOME/.config/radiotray-lite/` directory.

#### Options
Configuration file is located in the same directory as bookmarks file. It has simple XML format and following options are supported:
* `last_station` -- name of the last played station. Automatically updated, you don't need to change it.
* `buffer_size` -- size of the internal gstreamer's buffer.
* `buffer_duration` -- number of seconds to buffer.
* `url_timeout` -- timeout in seconds for fetching playlist.
* `notifications` -- if set to `false` disables desktop notification messages. Default is `true`.

Example:

```xml
<?xml version="1.0"?>
<config>
  <option name="last_station" value="Rock 181" />
  <option name="buffer_size" value="102400" />
  <option name="buffer_duration" value="2" />
  <option name="url_timeout" value="5" />
  <option name="notifications" value="false" />
</config>
```

### Licensing
See [LICENSE.md](LICENSE.md) file for license information.
