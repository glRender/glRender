cmake_minimum_required (VERSION 2.8.11)

project("glRender")

set (glRender_MAJOR_VERSION 0)
set (glRender_MINOR_VERSION 12)
set (glRender_PATCH_VERSION 0)
set (glRender_VERSION ${glRender_MAJOR_VERSION}.${glRender_MINOR_VERSION}.${glRender_PATCH_VERSION})

option(BUILD_ID "Build ID")

if (BUILD_ID STREQUAL "" OR BUILD_ID STREQUAL OFF)
	set(BUILD_ID "-")
endif()

message(STATUS ${BUILD_ID})

add_subdirectory (lib)
add_subdirectory (tests/unit-tests)
add_subdirectory (tests/integration-tests/glutApp)
add_subdirectory (tests/integration-tests/qtApp)
add_subdirectory (package)
