cmake_minimum_required (VERSION 2.8.11)

project("glRender")

set (glRender_VERSION_MAJOR 0)
set (glRender_VERSION_MINOR 8)
set (glRender_VERSION_PATCH 0)

# INSTALL(FILES "cmake/Modules/FindglRender.cmake" DESTINATION ${CMAKE_ROOT}/Modules/)

option(WithTests "Run tests" ON)
option(Arch "Target arch" "x64")

if (${Arch} STREQUAL "x64")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64")
    message(STATUS "Build for x64")
endif()

if (${Arch} STREQUAL "x86")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
    message(STATUS "Build for x86")
endif()

add_subdirectory (lib)
add_subdirectory (package)

if (WithTests)
    message(STATUS "Build with tests")
    add_subdirectory (tests)
endif()
