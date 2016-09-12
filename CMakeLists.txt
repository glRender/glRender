cmake_minimum_required (VERSION 2.8.11)

set (CMAKE_CXX_STANDARD 11)

aux_source_directory(src SRC_LIST)
add_library (glRender SHARED ${SRC_LIST})

find_package(OpenGL REQUIRED)

target_link_libraries(
        glRender
)

target_include_directories (glRender
    PUBLIC
    include
    ${CMAKE_CURRENT_SOURCE_DIR}
)

file(COPY include DESTINATION ${CMAKE_CURRENT_BINARY_DIR})