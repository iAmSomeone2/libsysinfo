cmake_minimum_required(VERSION 3.20)

project(libsysinfo LANGUAGES C)
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)
set(PROJECT_VERSION_PATCH 0)

include_directories(inc)

add_subdirectory(src)
