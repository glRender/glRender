cmake_minimum_required (VERSION 2.8.11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -pedantic")

if(CMAKE_SYSTEM_NAME STREQUAL "Linux" AND NOT ANDROID)
    set(LINUX 1)
endif(CMAKE_SYSTEM_NAME STREQUAL "Linux" AND NOT ANDROID)

if (LINUX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ldl")
endif()

aux_source_directory(src GLRENDER_SRC_LIST)
aux_source_directory(libs/glad/src GLRENDER_SRC_LIST)
add_library (glRender SHARED ${GLRENDER_SRC_LIST})

target_include_directories (glRender PUBLIC
    include
)

target_link_libraries(
    glRender
)

include_directories (
    libs/glad/include
    libs/
)

# Refresh include directory
file(REMOVE ${CMAKE_CURRENT_BINARY_DIR}/include)
file(COPY include DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

if(WIN32)
    set(LIB_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include PARENT_SCOPE)
    set(LIB_LIBRARIES ${CMAKE_CURRENT_BINARY_DIR}/libglRender.dll PARENT_SCOPE)
else()
    set(LIB_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include PARENT_SCOPE)
    set(LIB_LIBRARIES ${CMAKE_CURRENT_BINARY_DIR}/libglRender.so PARENT_SCOPE)
endif()
