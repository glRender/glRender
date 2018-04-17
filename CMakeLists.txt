cmake_minimum_required (VERSION 2.8.11)

project("glRender")

execute_process(
  COMMAND git describe --tags --dirty --always
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE glRender_VERSION
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

string(REPLACE "." ";" VERSION_LIST ${glRender_VERSION})

list(GET VERSION_LIST 0 DIRTY_MAJOR_VERSION)
string(REPLACE "v" "" glRender_MAJOR_VERSION ${DIRTY_MAJOR_VERSION})

list(GET VERSION_LIST 1 glRender_MINOR_VERSION)
list(GET VERSION_LIST 2 glRender_PATCH_VERSION)


#set (glRender_MAJOR_VERSION 0)
#set (glRender_MINOR_VERSION 12)
#set (glRender_PATCH_VERSION 3)
#set (glRender_VERSION ${glRender_MAJOR_VERSION}.${glRender_MINOR_VERSION}.${glRender_PATCH_VERSION})

option(BUILD_ID "Build ID")

if (BUILD_ID STREQUAL "" OR BUILD_ID STREQUAL OFF)
	set(BUILD_ID "-")
endif()

add_subdirectory (lib)
add_subdirectory (tests/unit-tests)
add_subdirectory (tests/integration-tests/glutApp)
add_subdirectory (tests/integration-tests/qtApp)
add_subdirectory (package)
