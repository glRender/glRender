cmake_minimum_required (VERSION 2.8.11)

add_compile_options(-std=c++11)

aux_source_directory(src GLRENDER_SRC_LIST)
add_library (glRender SHARED ${GLRENDER_SRC_LIST})

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

target_include_directories (glRender PUBLIC include)

target_link_libraries(
        glRender
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
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
