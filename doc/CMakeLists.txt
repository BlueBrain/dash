
# Copyright (c) 2011 Stefan Eilemann <Stefan.Eilemann@epfl.ch>

find_package(Doxygen)
if(DOXYGEN_FOUND)
  if(DASH_RELEASE)
    set(DASH_DOXYGEN_VERSION ${VERSION})
  else()
    set(DASH_DOXYGEN_VERSION ${VERSION}-git)
  endif()

  configure_file(DoxygenLayout.xml ${CMAKE_CURRENT_BINARY_DIR}/DoxygenLayout.xml
                 @ONLY)
  configure_file(Doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
  add_custom_target(doxygen ALL
    ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation using doxygen" VERBATIM)
  make_directory(${CMAKE_CURRENT_BINARY_DIR}/html)
  make_directory(${CMAKE_CURRENT_BINARY_DIR}/man/man3)
  install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/man/man3 DESTINATION man
          COMPONENT man PATTERN "*_docs_*" EXCLUDE)
  install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html
          DESTINATION share/dash-${VERSION_MAJOR} COMPONENT doc)
endif()

#install(FILES RELNOTES.txt AUTHORS CHANGES.txt ACKNOWLEDGEMENTS LGPL LICENSE.txt
#  DESTINATION share/dash/doc COMPONENT doc)

