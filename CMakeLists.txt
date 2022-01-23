cmake_minimum_required(VERSION 3.20)

project(libsysinfo LANGUAGES C)
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)
set(PROJECT_VERSION_PATCH 0)

# Set OS-dependent vars
if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    set(os_dir "linux")
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    set(os_dir "macOS")
else()
    set(os_dir "")
endif()

include_directories(inc)

add_subdirectory(src)
