# Copyright (c) 2012 Stefan.Eilemann@epfl.ch

# Info: http://www.itk.org/Wiki/CMake:Component_Install_With_CPack

set(CPACK_PACKAGE_VENDOR "bluebrain.epfl.ch")
set(CPACK_PACKAGE_CONTACT "Stefan Eilemann <Stefan.Eilemann@epfl.ch>")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY
 "Library for generic, efficient and thread-safe Data Access and Sharing")
set(CPACK_DEBIAN_PACKAGE_DEPENDS
 "libstdc++6, libboost-serialization-dev, ${LUNCHBOX_DEB_DEPENDENCIES}")

set(CPACK_MACPORTS_CATEGORY devel)
set(CPACK_MACPORTS_DEPENDS boost Lunchbox)

include(CommonCPack)
