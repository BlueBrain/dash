# Copyright (c) 2012 Stefan.Eilemann@epfl.ch

# Info: http://www.itk.org/Wiki/CMake:Component_Install_With_CPack

set(CPACK_PROJECT_NAME "libdash")
set(CPACK_PACKAGE_VENDOR "bluebrain.epfl.ch")
set(CPACK_PACKAGE_CONTACT "Stefan Eilemann <Stefan.Eilemann@epfl.ch>")
set(CPACK_DEBIAN_PACKAGE_DEPENDS
 "libstdc++6, libboost-serialization-dev, ${LUNCHBOX_DEV_DEPENDENCY}")

set(CPACK_MACPORTS_CATEGORY devel)
set(CPACK_MACPORTS_DEPENDS boost Lunchbox)

set(CPACK_PACKAGE_LICENSE "LGPL")
include(CommonCPack)
