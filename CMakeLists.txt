
# Copyright (c) 2011-2012 Stefan Eilemann <Stefan.Eilemann@epfl.ch>

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(dash)
set(CMAKE_MACPORTS_NAME libdash)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMake)
list(APPEND CMAKE_PREFIX_PATH ${SystemDrive}:/cygwin/bin)

set(VERSION_MAJOR "1")
set(VERSION_MINOR "0")
set(VERSION_PATCH "0")
set(RELEASE_VERSION OFF) # OFF or ABI version
set(LAST_RELEASE 1.0.0)

include(Common)
include(FindPackages)
include(GitTargets)

# add_subdirectory(examples)
add_subdirectory(dash)
add_subdirectory(tests)
include(DoxygenRule)

include(CTest)
include(CPackConfig)
