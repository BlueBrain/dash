
# Copyright (c) 2011-2012 Stefan Eilemann <Stefan.Eilemann@epfl.ch>

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(dash)
set(CMAKE_MACPORTS_NAME libdash)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMake)
list(APPEND CMAKE_PREFIX_PATH ${SystemDrive}:/cygwin/bin)

set(VERSION_MAJOR "1")
set(VERSION_MINOR "1")
set(VERSION_PATCH "0")
set(RELEASE_VERSION OFF) # OFF or ABI version
set(LAST_RELEASE 1.0.0)

include(Common)
include(GitTargets)
include(FindPackages)
set(DASH_TRANSIENT_LIBRARIES Lunchbox)

# add_subdirectory(examples)
add_subdirectory(dash)
add_subdirectory(tests)

file(GLOB DOC_PDF_FILES ${CMAKE_SOURCE_DIR}/doc/*.pdf)
foreach(DOC_PDF_FILE ${DOC_PDF_FILES})
  set(DOXYGEN_PDF_FILES "${DOXYGEN_PDF_FILES} ${DOC_PDF_FILE}")
endforeach()
include(DoxygenRule)

include(CTest)
include(CPackConfig)
include(PackageConfig)
