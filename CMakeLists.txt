
# Copyright (c) 2011-2012 Stefan Eilemann <Stefan.Eilemann@epfl.ch>

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(dash)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMake)
list(APPEND CMAKE_PREFIX_PATH ${SystemDrive}:/cygwin/bin)

set(VERSION_MAJOR "1")
set(VERSION_MINOR "0")
set(VERSION_PATCH "1")
set(RELEASE_VERSION 1) # OFF or ABI version

include(Common)
include(FindPackages)
include(GitTargets)

# add_subdirectory(examples)
add_subdirectory(dash)
add_subdirectory(tests)
include(DoxygenRule)

include(CTest)
include(CPackConfig)
