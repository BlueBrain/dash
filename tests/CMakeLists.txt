
# Copyright (c) 2011-2012 Stefan Eilemann <Stefan.Eilemann@epfl.ch>

# Change this number when adding tests to force a CMake run: 2

include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR})

if(NOT WIN32)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${dash_BINARY_DIR}/tests)
endif()

file(GLOB_RECURSE TEST_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

set(ALL_TESTS)
foreach(FILE ${TEST_FILES})
  string(REGEX REPLACE ".cpp" "" NAME ${FILE})
  string(REGEX REPLACE "[./]" "_" NAME ${NAME})

  source_group(\\ FILES ${FILE})
  add_executable(${NAME} ${FILE} common.cxx)
  set_target_properties(${NAME} PROPERTIES FOLDER "Tests")

  target_link_libraries(${NAME} dash)

  get_target_property(EXECUTABLE ${NAME} LOCATION)
  STRING(REGEX REPLACE "\\$\\(.*\\)" "\${CTEST_CONFIGURATION_TYPE}"
    EXECUTABLE "${EXECUTABLE}")
  add_test(${NAME} ${EXECUTABLE})
  set_target_properties(${NAME} PROPERTIES FOLDER "Tests")
  if(APPLE)
    set_property(TEST ${NAME} PROPERTY ENVIRONMENT
      "DYLD_LIBRARY_PATH=${LUNCHBOX_LIBRARY_DIR}:$ENV{DYLD_LIBRARY_PATH}"
      )
  endif()
  list(APPEND ALL_TESTS ${NAME})
endforeach(FILE ${TEST_FILES})

# workaround bug that tests won't get built
add_custom_target(tests COMMAND ${CMAKE_CTEST_COMMAND} DEPENDS ${ALL_TESTS})
set_target_properties(tests PROPERTIES FOLDER "Tests")

set(CTEST_CUSTOM_WARNING_EXCEPTION ${CTEST_CUSTOM_WARNING_EXCEPTION}
  # http://public.kitware.com/Bug/view.php?id=10179
  "ld: warning: duplicate dylib")
include(CTest)
