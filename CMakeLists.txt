cmake_minimum_required (VERSION 2.8.11)

set (CMAKE_CXX_STANDARD 11)

aux_source_directory(src SRC_LIST)
add_library (glRender ${SRC_LIST})

find_package(OpenGL REQUIRED)

target_link_libraries(
        glRender
        ${OPENGL_LIBRARIES}
)

target_include_directories (glRender PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${OPENGL_INCLUDE_DIR}
)