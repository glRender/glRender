cmake_minimum_required (VERSION 2.8.11)

# build a CPack driven installer package
# include (InstallRequiredSystemLibraries)
set (CPACK_PACKAGE_VERSION_MAJOR "${glRender_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${glRender_VERSION_MINOR}")
set (CPACK_PACKAGE_VERSION_PATCH "${glRender_VERSION_PATCH}")
set (CPACK_PACKAGE_VERSION "${CPACK_PACKAGE_VERSION_MAJOR}.${glRender_VERSION_MINOR}.${glRender_VERSION_PATCH}")
set (CPACK_PACKAGE_VENDOR "Aleksandr Lizin <sogimu@nxt.ru>")
set (CPACK_PACKAGE_DESCRIPTION_SUMMARY "It’s small library writen under C++ for 3d visualization with help of OpenGL 3.x. and a few repos with examples of using library. The main target it’s geting experience with 3d computer graphics.")
set (CPACK_SOURCE_GENERATOR "ZIP")

if(CMAKE_SYSTEM_NAME STREQUAL "Linux" AND NOT ANDROID)
    set(CPACK_GENERATOR "DEB")
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Aleksandr Lizin <sogimu@nxt.ru>")
    set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>= 2.3.1-6), libgcc1 (>= 1:3.4.2-12)")
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(CPACK_GENERATOR "NSIS")
endif()

include (CPack)