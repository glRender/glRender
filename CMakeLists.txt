cmake_minimum_required (VERSION 2.8.11)

project(glRender)

set (glRender_VERSION_MAJOR 0)
set (glRender_VERSION_MINOR 8)
set (glRender_VERSION_PATCH 0)

add_subdirectory (lib)
# add_subdirectory (tests)

# set(GLRENDER_INCLUDE_DIR ${LIB_INCLUDE_DIR} PARENT_SCOPE)
# set(GLRENDER_LIBRARIES   ${LIB_LIBRARIES} PARENT_SCOPE)

# build a CPack driven installer package
include (InstallRequiredSystemLibraries)
set (CPACK_PACKAGE_VERSION_MAJOR "${glRender_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${glRender_VERSION_MINOR}")
set (CPACK_PACKAGE_VERSION_PATCH "${glRender_VERSION_PATCH}")

SET(CPACK_GENERATOR "DEB")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Aleksandr Lizin <sogimu@nxt.ru>")
SET(CPACK_PACKAGE_VENDOR "Me, myself, and I")
SET(CPACK_SET_DESTDIR true)
SET(CPACK_INSTALL_PREFIX "/opt/glRender_${glRender_VERSION_MAJOR}.${glRender_VERSION_MINOR}.${glRender_VERSION_PATCH}")
SET(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>= 2.3.1-6), libgcc1 (>= 1:3.4.2-12)")

include (CPack)
