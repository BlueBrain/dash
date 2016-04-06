
# Copyright (c) 2011-2015 Stefan Eilemann <Stefan.Eilemann@epfl.ch>

cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(dash VERSION 1.1.0)
set(dash_VERSION_ABI 2)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake
  ${CMAKE_SOURCE_DIR}/CMake/common)

include(GitExternal)

set(DASH_PACKAGE_URL https://launchpad.net/~eilemann/+archive/equalizer)
set(CMAKE_MACPORTS_NAME libdash)
include(Common)
set(COMMON_PROJECT_DOMAIN ch.epfl.bluebrain)
set(DASH_DESCRIPTION
 "C++ library for generic, efficient and thread-safe Data Access and Sharing")
set(DASH_DEPENDENT_LIBRARIES Lunchbox)
set(DASH_DEB_DEPENDS libboost-serialization-dev)

set(DASH_ISSUES_URL "https://github.com/BlueBrain/dash/issues")
set(DASH_MAINTAINER
  "BBP Visualization Team <bbp-open-source@googlegroups.com>")
set(DASH_LICENSE LGPL)

common_find_package(Boost REQUIRED COMPONENTS serialization)
common_find_package(Lunchbox REQUIRED)
common_find_package_post()

add_subdirectory(dash)
add_subdirectory(tests)

file(GLOB DOC_PDF_FILES ${PROJECT_SOURCE_DIR}/doc/*.pdf)
foreach(DOC_PDF_FILE ${DOC_PDF_FILES})
  set(DOXYGEN_EXTRA_FILES "${DOXYGEN_EXTRA_FILES} ${DOC_PDF_FILE}")
endforeach()
include(CPackConfig)

set(DOXYGEN_MAINPAGE_MD README.md)
set(DOXYGEN_EXTRA_INPUT ${PROJECT_SOURCE_DIR}/README.md)
set(DOXYGEN_EXTRA_EXCLUDE ${CMAKE_INSTALL_PREFIX}/include/dash/detail)
include(DoxygenRule)
