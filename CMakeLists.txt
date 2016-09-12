cmake_minimum_required (VERSION 2.8.11)

set (CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)

aux_source_directory(src SRC_LIST)
add_library (glRender SHARED ${SRC_LIST})

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

target_link_libraries(
        glRender
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
)

target_include_directories (glRender
    PUBLIC
    include
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${OPENGL_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIRS}
)