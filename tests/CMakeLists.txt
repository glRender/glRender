cmake_minimum_required (VERSION 2.8.11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -pedantic")

if(CMAKE_SYSTEM_NAME STREQUAL "Linux" AND NOT ANDROID)
    set(LINUX 1)
endif(CMAKE_SYSTEM_NAME STREQUAL "Linux" AND NOT ANDROID)

if (LINUX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ldl")
endif()

set (CATCH_INCLUDES libs/Catch/include)

set (SRC src)
set (bin_src
    ${SRC}/main.cpp
    # ${SRC}/vec3.cpp
    ${SRC}/aabb.cpp
)

include_directories (${SRC} ${LIB_INCLUDE_DIR} ${CATCH_INCLUDES})

add_executable(Tests ${bin_src})

target_link_libraries (Tests ${LIB_LIBRARIES})
