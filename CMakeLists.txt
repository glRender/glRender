cmake_minimum_required (VERSION 2.8.11)

project(glRender)

set (glRender_VERSION_MAJOR 0)
set (glRender_VERSION_MINOR 8)
set (glRender_VERSION_PATCH 0)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux" AND NOT ANDROID)
    set(LINUX 1)
endif(CMAKE_SYSTEM_NAME STREQUAL "Linux" AND NOT ANDROID)

add_subdirectory (lib)
# add_subdirectory (tests)

INSTALL(FILES "cmake/Modules/FindglRender.cmake" DESTINATION ${CMAKE_ROOT}/Modules/)

# build a CPack driven installer package
# include (InstallRequiredSystemLibraries)
set (CPACK_PACKAGE_VERSION_MAJOR "${glRender_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${glRender_VERSION_MINOR}")
set (CPACK_PACKAGE_VERSION_PATCH "${glRender_VERSION_PATCH}")

set(CPACK_PACKAGE_VENDOR "Aleksandr Lizin <sogimu@nxt.ru>")

if(LINUX)
    set(CPACK_GENERATOR "DEB")
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Aleksandr Lizin <sogimu@nxt.ru>")
    # set(CPACK_SET_DESTDIR true)
    # set(CPACK_INSTALL_PREFIX "/opt/glRender_${glRender_VERSION_MAJOR}.${glRender_VERSION_MINOR}.${glRender_VERSION_PATCH}")
    set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>= 2.3.1-6), libgcc1 (>= 1:3.4.2-12)")
endif()

include (CPack)