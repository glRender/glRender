set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall  -Werror -pedantic -Wno-parentheses -Wl,-no-as-needed")

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

set_source_files_properties(${SRCROOT}/ImageLoader.cpp PROPERTIES COMPILE_FLAGS -fno-strict-aliasing)

include_directories (libs/glad/include/ libs/ include/)
add_library (glRender SHARED ${SRC_FILES})
target_include_directories (glRender PUBLIC include)

# Refresh include directory
file(REMOVE ${CMAKE_CURRENT_BINARY_DIR}/include)
file(COPY include DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

INSTALL(DIRECTORY "include/"  DESTINATION "include/glRender")
INSTALL(TARGETS "glRender" DESTINATION "lib/glRender")