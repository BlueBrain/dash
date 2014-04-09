
# Copyright (c) 2011-2014 Stefan Eilemann <Stefan.Eilemann@epfl.ch>

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(dash)
set(CMAKE_MACPORTS_NAME libdash)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake
  ${CMAKE_SOURCE_DIR}/CMake/common)

include(GitExternal)
include(Buildyard)
if(BUILDYARD_STOP)
  return()
endif()
list(APPEND CMAKE_PREFIX_PATH ${SystemDrive}:/cygwin/bin)

set(RELEASE_VERSION OFF) # OFF or ABI version
set(LAST_RELEASE 1.0.1)
set(VERSION_MAJOR "1")
set(VERSION_MINOR "1")
set(VERSION_PATCH "0")

set(DASH_DESCRIPTION
 "C++ library for generic, efficient and thread-safe Data Access and Sharing")
set(COMMON_PROJECT_DOMAIN ch.epfl.bluebrain)
set(DASH_PACKAGE_URL https://launchpad.net/~eilemann/+archive/equalizer)
include(Common)
include(FindPackages)
set(DASH_DEPENDENT_LIBRARIES Lunchbox)

add_subdirectory(dash)
add_subdirectory(tests)

file(GLOB DOC_PDF_FILES ${CMAKE_SOURCE_DIR}/doc/*.pdf)
foreach(DOC_PDF_FILE ${DOC_PDF_FILES})
  set(DOXYGEN_EXTRA_FILES "${DOXYGEN_EXTRA_FILES} ${DOC_PDF_FILE}")
endforeach()
include(CPackConfig)

set(DOXYGEN_MAINPAGE_MD README.md)
set(DOXYGEN_EXTRA_INPUT @dash_SOURCE_DIR@/README.md)
set(DOXYGEN_EXTRA_EXCLUDE @CMAKE_INSTALL_PREFIX@/include/dash/detail)
include(DoxygenRule)
