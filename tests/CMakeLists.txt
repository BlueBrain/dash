
include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR})

if(WIN32)
  get_filename_component(CO_DIR ${COLLAGE_LIBRARIES} PATH)
  set(CO_DIR "${CO_DIR}/../bin")
  file(COPY "${CO_DIR}/Collage.dll" "${CO_DIR}/pthread.dll"
       DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug)
  file(COPY "${CO_DIR}/Collage.dll" "${CO_DIR}/pthread.dll"
       DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release)
  file(COPY "${CO_DIR}/Collage.dll" "${CO_DIR}/pthread.dll"
       DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/RelWithDebInfo)
  file(COPY "${CO_DIR}/Collage.dll" "${CO_DIR}/pthread.dll"
       DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/MinSizeRel)
  # dont set output dir, tests want to be with DLLs on Windows - no rpath
else()
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${dash_BINARY_DIR}/tests)
endif()

file(GLOB_RECURSE TEST_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

set(ALL_TESTS)
foreach(FILE ${TEST_FILES})
  string(REGEX REPLACE "[./]" "_" NAME ${FILE})
  source_group(\\ FILES ${FILE})
  add_executable(${NAME} ${FILE})
  target_link_libraries(${NAME} dash)
  get_target_property(EXECUTABLE ${NAME} LOCATION)
  STRING(REGEX REPLACE "\\$\\(.*\\)" "\${CTEST_CONFIGURATION_TYPE}"
    EXECUTABLE "${EXECUTABLE}")
  add_test(${NAME} ${EXECUTABLE})
  set_target_properties(${NAME} PROPERTIES FOLDER "Tests")
  if(APPLE)
    set_property(TEST ${NAME} PROPERTY ENVIRONMENT
      "DYLD_LIBRARY_PATH=${COLLAGE_LIBRARY_DIR}:$ENV{DYLD_LIBRARY_PATH}"
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
