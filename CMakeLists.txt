cmake_minimum_required (VERSION 2.8.11)

project("glRender")

set (glRender_MAJOR_VERSION 0)
set (glRender_MINOR_VERSION 8)
set (glRender_PATCH_VERSION 7)
set (glRender_VERSION ${glRender_MAJOR_VERSION}.${glRender_MINOR_VERSION}.${glRender_PATCH_VERSION})

add_subdirectory (lib)
add_subdirectory (tests/unit-tests)
add_subdirectory (tests/integration-tests/glutApp)
add_subdirectory (package)
