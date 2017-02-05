set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -pedantic -Wno-parentheses -Wl,-no-as-needed")

if(CMAKE_SYSTEM_NAME STREQUAL "Linux" AND NOT ANDROID)
    set(LINUX 1)
endif(CMAKE_SYSTEM_NAME STREQUAL "Linux" AND NOT ANDROID)

if (LINUX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ldl -lgcc_s -lgcc")
endif()

set (SRC_PATH src)
set (GLAD_PATH libs/glad/src)

aux_source_directory(${SRC_PATH} SRC_FILES)
aux_source_directory(${GLAD_PATH} SRC_FILES)

include_directories (libs/glad/include/ libs/ include/)
add_library (glRender SHARED ${SRC_FILES})
target_include_directories (glRender PUBLIC include)

# Refresh include directory
file(REMOVE ${CMAKE_CURRENT_BINARY_DIR}/include)
file(COPY include DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

INSTALL(DIRECTORY "include/"  DESTINATION "include/glRender")
INSTALL(TARGETS "glRender" DESTINATION "lib/glRender")