cmake_minimum_required (VERSION 2.8.11)

set (CMAKE_CXX_STANDARD 11)

aux_source_directory(src GLRENDER_SRC_LIST)
add_library (glRender SHARED ${GLRENDER_SRC_LIST})

target_include_directories (glRender PUBLIC include)

# Refresh include directory
file(REMOVE ${CMAKE_CURRENT_BINARY_DIR}/include)
file(COPY include DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

set(LIB_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include PARENT_SCOPE)
set(LIB_LIBRARIES ${CMAKE_CURRENT_BINARY_DIR}/libglRender.so PARENT_SCOPE)
