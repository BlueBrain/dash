
# Copyright (c) 2011-2012 Stefan Eilemann <Stefan.Eilemann@epfl.ch>

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(dash)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMake)
list(APPEND CMAKE_PREFIX_PATH ${SystemDrive}:/cygwin/bin)

set(VERSION_MAJOR "0")
set(VERSION_MINOR "1")
set(VERSION_PATCH "0")

set(VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})
if(VERSION_MINOR VERSION_LESS 10)
  set(VERSION_ABI ${VERSION_MAJOR}0${VERSION_MINOR})
else()
  set(VERSION_ABI ${VERSION_MAJOR}${VERSION_MINOR})
endif()

include(Common)

find_package(Boost 1.41 REQUIRED serialization)
link_directories(${Boost_LIBRARY_DIRS})
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})

find_package(Lunchbox 0.9.0 REQUIRED)
link_directories(${LUNCHBOX_LIBRARY_DIRS})
include_directories(${LUNCHBOX_INCLUDE_DIRS})

include(InstallSymlink)
# add_subdirectory(examples)
add_subdirectory(dash)
add_subdirectory(tests)
add_subdirectory(doc)

include(CTest)
add_custom_target(package COMMENT "Packaging not done yet")
# include(CPackConfig)
