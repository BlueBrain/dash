
# Copyright (c) 2011-2014 Stefan Eilemann <Stefan.Eilemann@epfl.ch>

set(DASH_PUBLIC_HEADERS # public, installed
  attribute.h
  commit.h
  context.h
  node.h
  nodeVisitor.h
  types.h
  visitorResult.h
  # private, installed
  detail/attribute.h
  detail/attributeIterator.h
  detail/change.h
  detail/childIterator.h
  detail/commit.h
  detail/commitChange.h
  detail/context.h
  detail/contextCommit.h
  detail/contextPtr.h
  detail/node.h
  detail/parentIterator.h
  detail/serializable.h
  detail/types.h
)

set(DASH_SOURCES
  attribute.cpp
  context.cpp
  commit.cpp
  node.cpp
  detail/attribute.cpp
  detail/change.cpp
  detail/commit.cpp
  detail/commitChange.cpp
  detail/context.cpp
  detail/contextChange.cpp
  detail/contextChange.h
  detail/contextCommit.cpp
  detail/node.cpp
)

set(DASH_LINK_LIBRARIES PUBLIC Lunchbox ${Boost_LIBRARIES})

source_group(\\ FILES CMakeLists.txt ${DASH_ALL})
source_group(detail FILES ${DASH_DETAIL_ALL})

common_library(dash)
