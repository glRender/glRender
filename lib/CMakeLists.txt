set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall  -Werror -pedantic -Wno-parentheses -Wl,-no-as-needed")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} -O3")

if (CMAKE_SYSTEM_NAME STREQUAL "Linux" AND NOT ANDROID)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ldl")
endif()

if (MINGW)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-misleading-indentation")
endif()

set (SRC_PATH src)
set (GLAD_PATH libs/glad/src)

aux_source_directory(${SRC_PATH} SRC_FILES)
aux_source_directory(${GLAD_PATH} SRC_FILES)

include_directories (libs/glad/include/ libs/ include/)
add_library (glRender SHARED ${SRC_FILES})

target_include_directories (glRender PUBLIC include)

if (CMAKE_SYSTEM_NAME STREQUAL "Linux" AND NOT ANDROID)
    target_link_libraries(glRender gcc_s gcc)
endif()

# Refresh include directory
file(REMOVE ${CMAKE_CURRENT_BINARY_DIR}/include)
file(COPY include DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(REMOVE ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
file(COPY Doxyfile DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

INSTALL(DIRECTORY 
    "include/"  
    DESTINATION "include/glRender" COMPONENT dev)

INSTALL(TARGETS 
    "glRender"
    DESTINATION "lib")

configure_file(Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/glRenderConfig.cmake" @ONLY)

configure_file(ConfigVersion.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/glRenderConfigVersion.cmake" @ONLY)

if(WIN32 AND NOT CYGWIN)
  set(DEF_INSTALL_CMAKE_DIR CMake)
else()
  set(DEF_INSTALL_CMAKE_DIR lib/cmake/glRender)
endif()
set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH
  "Installation directory for CMake files")

install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/glRenderConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/glRenderConfigVersion.cmake"
  DESTINATION "${INSTALL_CMAKE_DIR}" COMPONENT dev)
