cmake_minimum_required (VERSION 2.8.11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -pedantic -Wno-parentheses")

set (SRC_PATH src)
set (CATCH_PATH libs/Catch/include)

aux_source_directory(${SRC_PATH} SRC_FILES)
set (SRC_FILES ${SRC_FILES}
#     ${SRC_PATH}/vec3.cpp
#     ${SRC_PATH}/aabb.cpp
#     ${SRC_PATH}/test.cpp
     main.cpp
)

add_executable(tests ${SRC_FILES})
include_directories(
	${TEST_SRC_PATH} ${CATCH_PATH} 
    ${PROJECT_BINARY_DIR}/lib/include
)

target_link_libraries (tests glRender)

if (CMAKE_SYSTEM_NAME STREQUAL "Linux" AND NOT ANDROID)
  add_custom_command(TARGET glutApp
    PRE_BUILD
    COMMAND "${CMAKE_COMMAND}" -E make_directory "${CMAKE_CURRENT_BINARY_DIR}/libs/"
    COMMAND "${CMAKE_COMMAND}" -E copy "${CMAKE_BINARY_DIR}/lib/libglRender.so"                           "${CMAKE_CURRENT_BINARY_DIR}/libs/"
    COMMAND "${CMAKE_COMMAND}" -E copy "${CMAKE_BINARY_DIR}/lib/libglRender.so.${glRender_MAJOR_VERSION}" "${CMAKE_CURRENT_BINARY_DIR}/libs/"
    COMMAND "${CMAKE_COMMAND}" -E copy "${CMAKE_BINARY_DIR}/lib/libglRender.so.${glRender_VERSION}"       "${CMAKE_CURRENT_BINARY_DIR}/libs/"
  )
endif()

if (WIN32)
  add_custom_command(TARGET glutApp
    PRE_BUILD
    COMMAND "${CMAKE_COMMAND}" -E make_directory "${CMAKE_CURRENT_BINARY_DIR}/libs/"
    COMMAND "${CMAKE_COMMAND}" -E copy "${CMAKE_BINARY_DIR}/lib/glRender.dll"                           "${CMAKE_CURRENT_BINARY_DIR}/libs/"
  )
endif()
 