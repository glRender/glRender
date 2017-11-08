cmake_minimum_required (VERSION 2.8.11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

if (CMAKE_SYSTEM_NAME STREQUAL "Linux" AND NOT ANDROID)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
	set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} -O3")
endif()

if (WIN32)
	set(CMAKE_SYSTEM_PREFIX_PATH "C:\\freeglut")
endif()

aux_source_directory(src SOURCES)
add_executable (glutApp ${SOURCES})

find_package(GLUT REQUIRED)

include_directories(
  ${GLUT_INCLUDE_DIR}
  ${PROJECT_BINARY_DIR}/lib/include
)

set(CMAKE_INSTALL_RPATH ".")

target_link_libraries(glutApp
  ${GLUT_LIBRARIES}
  glRender
)

add_custom_command(TARGET glutApp
  PRE_BUILD
  COMMAND "${CMAKE_COMMAND}" -E make_directory "${CMAKE_CURRENT_BINARY_DIR}/libs/"
  COMMAND "${CMAKE_COMMAND}" -E copy "${CMAKE_BINARY_DIR}/lib/libglRender.so"                           "${CMAKE_CURRENT_BINARY_DIR}/libs/"
  COMMAND "${CMAKE_COMMAND}" -E copy "${CMAKE_BINARY_DIR}/lib/libglRender.so.${glRender_MAJOR_VERSION}" "${CMAKE_CURRENT_BINARY_DIR}/libs/"
  COMMAND "${CMAKE_COMMAND}" -E copy "${CMAKE_BINARY_DIR}/lib/libglRender.so.${glRender_VERSION}"       "${CMAKE_CURRENT_BINARY_DIR}/libs/"
)

file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
