
# Copyright (c) 2011-2012 Stefan Eilemann <Stefan.Eilemann@epfl.ch>

configure_file("Version.h.in" "${CMAKE_CURRENT_BINARY_DIR}/Version.h" @ONLY)

set(DASH_HEADERS # public, installed
  api.h
  dash.h
  types.h
  Attribute.h
  Commit.h
  Context.h
  Node.h
  NodeVisitor.h
  "${CMAKE_CURRENT_BINARY_DIR}/Version.h"
  VisitorResult.h
)

set(DASH_DETAIL_HEADERS # private, installed
  detail/Any.h
  detail/AnySerialization.h
  detail/Attribute.h
  detail/AttributeIterator.h
  detail/Change.h
  detail/ChildIterator.h
  detail/Commit.h
  detail/Context.h
  detail/ContextPtr.h
  detail/Node.h
  detail/Serializable.h
  detail/types.h
)

set(DASH_SOURCES
  Attribute.cpp
  Context.cpp
  Commit.cpp
  Node.cpp
  Version.cpp
)

set(DASH_DETAIL_SOURCES
  detail/AnySerialization.cpp
  detail/Attribute.cpp  
  detail/Change.cpp
  detail/Commit.cpp
  detail/Context.cpp  
  detail/Node.cpp
)

set(DASH_ALL ${DASH_HEADERS} ${DASH_SOURCES})
set(DASH_DETAIL_ALL ${DASH_DETAIL_HEADERS} ${DASH_DETAIL_SOURCES})

source_group(\\ FILES CMakeLists.txt ${DASH_ALL})
source_group(detail FILES ${DASH_DETAIL_ALL})

set(LIBRARY dash)
set(LIB_INCLUDE ${LIBRARY})
if(NOT MSVC)
  set(LIB_INCLUDE ${LIB_INCLUDE}${VERSION_MAJOR})
endif()

add_library(${LIBRARY} SHARED ${DASH_ALL} ${DASH_DETAIL_ALL})
target_link_libraries(${LIBRARY} ${LUNCHBOX_LIBRARIES} ${Boost_LIBRARIES})
set_target_properties(${LIBRARY}
  PROPERTIES VERSION ${VERSION} SOVERSION ${VERSION_ABI}
  COMPILE_DEFINITIONS DASH_SHARED
)

install(FILES ${DASH_HEADERS}
        DESTINATION include/${LIB_INCLUDE} COMPONENT dev)
install(FILES ${DASH_DETAIL_HEADERS}
        DESTINATION include/${LIB_INCLUDE}/detail COMPONENT dev)
install(TARGETS ${LIBRARY}
        ARCHIVE DESTINATION lib COMPONENT dev
        RUNTIME DESTINATION bin COMPONENT lib
        LIBRARY DESTINATION lib COMPONENT lib)
if(NOT MSVC)
  install_symlink("include/${LIB_INCLUDE}" "include/${LIBRARY}" dev)
endif()
