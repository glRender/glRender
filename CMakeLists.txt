cmake_minimum_required (VERSION 2.8.11)

add_subdirectory (lib)
#add_subdirectory (tests)

set(GLRENDER_INCLUDE_DIR ${LIB_INCLUDE_DIR} PARENT_SCOPE)
set(GLRENDER_LIBRARIES   ${LIB_LIBRARIES} PARENT_SCOPE)
