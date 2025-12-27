cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(radiotray_lite)

include(FindPkgConfig)
include(CheckCXXCompilerFlag)
include(CheckCCompilerFlag)
include(CPack)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")

check_c_compiler_flag("-std=c11" COMPILER_SUPPORTS_C11)
if(NOT COMPILER_SUPPORTS_C11)
    message(FATAL_ERROR "The compiler ${CMAKE_C_COMPILER} has no C11 support.")
endif()

check_cxx_compiler_flag("-std=c++11" COMPILER_SUPPORTS_CXX11)
if(NOT COMPILER_SUPPORTS_CXX11)
    message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support.")
endif()

if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "CMAKE_BUILD_TYPE is not set, set to default = RelWithDebInfo")
    set(CMAKE_BUILD_TYPE "RelWithDebInfo")
endif()
message(STATUS "CMAKE_BUILD_TYPE: " ${CMAKE_BUILD_TYPE})

add_compile_options(-Wall)
add_compile_options(-Wextra)

set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -DELPP_NO_DEFAULT_LOG_FILE")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DELPP_NO_DEFAULT_LOG_FILE")

set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -s")

find_package(LibMagic REQUIRED)
if (NOT LIBMAGIC_FOUND)
    message(FATAL_ERROR "Couldn't find libmagic")
endif(NOT LIBMAGIC_FOUND)

find_package(Threads REQUIRED)
find_package(LibNotify REQUIRED)

pkg_check_modules(LIBXML2 REQUIRED libxml-2.0)
pkg_check_modules(GLIB2 REQUIRED glib-2.0)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)
pkg_check_modules(CURL REQUIRED libcurl)
pkg_check_modules(APPINDICATOR QUIET ayatana-appindicator3-0.1)
if (NOT APPINDICATOR_FOUND)
    pkg_check_modules(APPINDICATOR REQUIRED appindicator3-0.1)
endif()

pkg_check_modules(GSTREAMER QUIET gstreamer-1.0)
if (NOT GSTREAMER_FOUND)
    pkg_check_modules(GSTREAMER REQUIRED gstreamer-0.10)
endif()

pkg_check_modules(GSTREAMERMM QUIET gstreamermm-1.0)
if (NOT GSTREAMERMM_FOUND)
    pkg_check_modules(GSTREAMERMM REQUIRED gstreamermm-0.10)
endif()

set(TARGET_VERSION_MAJOR 0)
set(TARGET_VERSION_MINOR 2)
set(TARGET_VERSION_PATCH 19)
set(APP_VERSION "${TARGET_VERSION_MAJOR}.${TARGET_VERSION_MINOR}.${TARGET_VERSION_PATCH}")

add_subdirectory(src)

install(
    DIRECTORY data/images DESTINATION share/radiotray-lite/
)
install(
    FILES data/bookmarks.xml DESTINATION share/radiotray-lite/
)

install(
    FILES data/radiotray-lite.desktop DESTINATION share/applications/
)

install(
    FILES data/images/radiotray-lite.png DESTINATION share/pixmaps/
)

if(NOT CPACK_DEBIAN_PACKAGE_ARCHITECTURE)
    set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE amd64)
endif()

set(CPACK_PACKAGING_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})

# Prefer modern Debian/Ubuntu runtime deps when detected.
set(_deps_modern "libc6, libgtkmm-3.0-1v5 (>= 3.10.1), libgstreamermm-1.0-0v5 (>= 1.10.0) | libgstreamermm-1.0-1 (>= 1.10.0), gstreamer1.0-plugins-base (>= 1.2.4), gstreamer1.0-plugins-good (>= 1.2.4), gstreamer1.0-plugins-bad (>= 1.2.4), libcurl4 (>= 7.58.0), libnotify4 (>= 0.7.6), libayatana-appindicator3-1 | libappindicator3-1, libmagic1")
set(_deps_legacy "libc6, libgtkmm-3.0-1 | libgtkmm-3.0-1v5 (>= 3.10.1), libgstreamermm-0.10-2 (>= 0.10.11) | libgstreamermm-1.0-0v5 (>= 1.4.3) | libgstreamermm-1.0-1 (>= 1.10.0), gstreamer0.10-plugins-base (>= 0.10.36) | gstreamer1.0-plugins-base (>= 1.2.4), gstreamer0.10-plugins-good (>= 0.10.31) | gstreamer1.0-plugins-good (>= 1.2.4), gstreamer0.10-plugins-bad (>= 0.10.23) | gstreamer1.0-plugins-bad (>= 1.2.4), libcurl3 (>= 7.35.0) | libcurl4 (>= 7.58.0), libnotify4 (>= 0.7.6), libappindicator3-1, libmagic1")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "${_deps_legacy}")
if (EXISTS "/etc/os-release")
    file(READ "/etc/os-release" _os_release)
    string(REGEX MATCH "\nID=([A-Za-z0-9_-]+)" _match_id "${_os_release}")
    string(TOLOWER "${CMAKE_MATCH_1}" _os_id)
    if (_os_id STREQUAL "ubuntu" OR _os_id STREQUAL "debian")
        set(CPACK_DEBIAN_PACKAGE_DEPENDS "${_deps_modern}")
    endif()
endif()

configure_file(${PROJECT_SOURCE_DIR}/cmake/CPackConfig.cmake.in CPackConfig.cmake @ONLY)
