# - Try to find glRender
# Once done this will define
#
#  glRender_FOUND - system has libusb
#  glRender_INCLUDE_DIRS - the libusb include directory
#  glRender_LIBRARIES - Link these to use libusb
#
#
if (glRender_LIBRARIES AND glRender_INCLUDE_DIRS)
  # in cache already
  set(glRender_FOUND TRUE)
else (glRender_LIBRARIES AND glRender_INCLUDE_DIRS)
  find_path(glRender_INCLUDE_DIR
    NAMES
      glRender.h
    PATHS
      /usr/include
      /usr/local/include
      /opt/
    PATH_SUFFIXES
      glRender)

  find_library(glRender_LIBRARY
    NAMES
      glRender
    PATHS
      /usr/lib
      /usr/local/lib
    PATH_SUFFIXES
      glRender)

  set(glRender_INCLUDE_DIRS
    ${glRender_INCLUDE_DIR}
  )
  set(glRender_LIBRARIES
    ${glRender_LIBRARY}
)

  if (glRender_INCLUDE_DIRS AND glRender_LIBRARIES)
     set(glRender_FOUND TRUE)
  endif (glRender_INCLUDE_DIRS AND glRender_LIBRARIES)

  if (glRender_FOUND)
    if (NOT glRender_FIND_QUIETLY)
      message(STATUS "Found glRender:")
      message(STATUS " - Includes: ${glRender_INCLUDE_DIRS}")
      message(STATUS " - Libraries: ${glRender_LIBRARIES}")
    endif (NOT glRender_FIND_QUIETLY)
  else (glRender_FOUND)
    if (glRender_FIND_REQUIRED)
      message(FATAL_ERROR "Could not find glRender")
    endif (glRender_FIND_REQUIRED)
  endif (glRender_FOUND)

  # show the glRender_INCLUDE_DIRS and glRender_LIBRARIES variables only in the advanced view
  mark_as_advanced(glRender_INCLUDE_DIRS glRender_LIBRARIES)

endif (glRender_LIBRARIES AND glRender_INCLUDE_DIRS)