
# Copyright (c) 2011-2015 Stefan Eilemann <Stefan.Eilemann@epfl.ch>

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(dash)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake
  ${CMAKE_SOURCE_DIR}/CMake/common)

include(GitExternal)

set(VERSION_MAJOR "1")
set(VERSION_MINOR "1")
set(VERSION_PATCH "0")
set(VERSION_ABI 2)

set(DASH_PACKAGE_URL https://launchpad.net/~eilemann/+archive/equalizer)
set(CMAKE_MACPORTS_NAME libdash)
include(Common)
set(COMMON_PROJECT_DOMAIN ch.epfl.bluebrain)
set(DASH_DESCRIPTION
 "C++ library for generic, efficient and thread-safe Data Access and Sharing")
set(DASH_DEPENDENT_LIBRARIES Lunchbox)

set(DASH_ISSUES_URL "https://github.com/BlueBrain/dash/issues")
set(DASH_MAINTAINER
  "BBP Visualization Team <bbp-open-source@googlegroups.com>")
set(DASH_LICENSE LGPL)

common_package(Boost REQUIRED COMPONENTS serialization)
common_package(Lunchbox REQUIRED)
common_package_post()

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
