
set(DASH_PACKAGE_VERSION 1.0)
set(DASH_DEPENDS bluebrain REQUIRED Lunchbox Boost)
set(DASH_BOOST_COMPONENTS serialization)
set(DASH_DEB_DEPENDS libboost-serialization-dev)
set(DASH_REPO_URL https://github.com/BlueBrain/dash.git)

if(CI_BUILD_COMMIT)
  set(DASH_REPO_TAG ${CI_BUILD_COMMIT})
else()
  set(DASH_REPO_TAG master)
endif()
set(DASH_FORCE_BUILD ON)
set(DASH_SOURCE ${CMAKE_SOURCE_DIR})