
# Copyright (c) 2011 Stefan Eilemann <Stefan.Eilemann@epfl.ch>

configure_file("Version.h.in" "${CMAKE_CURRENT_BINARY_DIR}/Version.h" @ONLY)

set(DASH_HEADERS
  api.h
  dash.h
  types.h
  Attribute.h
  Commit.h
  Context.h
  Node.h
  NodeVisitor.h
  Vector.h
  "${CMAKE_CURRENT_BINARY_DIR}/Version.h"
  VisitorResult.h
)

set(DASH_DETAIL_HEADERS
  detail/AttributeIterator.h
  detail/ChildIterator.h
  detail/Iterator.h
  detail/VectorIterator.h
)

set(DASH_SOURCES
  Attribute.cpp
  Context.cpp
  Commit.cpp
  Node.cpp
  Version.cpp
)

set(DASH_DETAIL_SOURCES
  detail/Attribute.h
  detail/Attribute.cpp
  detail/Change.h
  detail/Change.cpp
  detail/ContextPtr.h
  detail/Commit.h
  detail/Commit.cpp
  detail/Context.h
  detail/Context.cpp
  detail/Node.h
  detail/Node.cpp
  detail/types.h
)

set(DASH_ALL ${DASH_HEADERS} ${DASH_SOURCES})
set(DASH_DETAIL_ALL ${DASH_DETAIL_HEADERS} ${DASH_DETAIL_SOURCES})

source_group(\\ FILES CMakeLists.txt ${DASH_ALL})
source_group(detail FILES ${DASH_DETAIL_ALL})

set(LIBRARY dash)
set(LIB_INCLUDE ${LIBRARY}${VERSION_MAJOR})

add_library(${LIBRARY} SHARED ${DASH_ALL} ${DASH_DETAIL_ALL})
target_link_libraries(${LIBRARY} ${COLLAGE_LIBRARIES})
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
install_symlink(${LIB_INCLUDE} ${LIBRARY} include)
