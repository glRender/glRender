cmake_minimum_required (VERSION 2.8.11)

# build a CPack driven installer package
# include (InstallRequiredSystemLibraries)
set (CPACK_PACKAGE_VERSION_MAJOR "${glRender_MAJOR_VERSION}")
set (CPACK_PACKAGE_VERSION_MINOR "${glRender_MINOR_VERSION}")
set (CPACK_PACKAGE_VERSION_PATCH "${glRender_PATCH_VERSION}")
set (CPACK_PACKAGE_VERSION "${glRender_VERSION}")
set (CPACK_PACKAGE_VENDOR "Aleksandr Lizin <sogimu@nxt.ru>")
set (CPACK_PACKAGE_DESCRIPTION_SUMMARY "It’s small library writen under C++ for 3d visualization with help of OpenGL 3.x. and a few repos with examples of using library. The main target it’s geting experience with 3d computer graphics.")

if(CMAKE_SYSTEM_NAME STREQUAL "Linux" AND NOT ANDROID)
    set(CPACK_GENERATOR "DEB")
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Aleksandr Lizin <sogimu@nxt.ru>")
    set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>= 2.3.1-6)")
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(CPACK_GENERATOR "NSIS")
    set(CPACK_NSIS_CONTACT "Aleksandr Lizin <sogimu@nxt.ru>")
    set(CPACK_NSIS_PACKAGE_NAME "glRender")
    set(CPACK_NSIS_DISPLAY_NAME "glRender")
    set(CPACK_NSIS_MODIFY_PATH ON)
    set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)
endif()

include (CPack)