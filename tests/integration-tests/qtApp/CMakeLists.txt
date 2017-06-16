cmake_minimum_required (VERSION 2.8.11)

set(CMAKE_BUILD_TYPE "Debug")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -pedantic")

set (SRC src)
set (lib_src ${SRC}/knot.cpp
            ${SRC}/mainwindow.cpp
            ${SRC}/model.cpp
            ${SRC}/polylinearea.cpp
            ${SRC}/polylineeditor.cpp
            ${SRC}/utils.cpp
            ${SRC}/Mark.cpp
)

set (lib_hdr ${SRC}/knot.h
            ${SRC}/mainwindow.h
            ${SRC}/model.h
            ${SRC}/polylinearea.h
            ${SRC}/polylineeditor.h
            ${SRC}/utils.h
            ${SRC}/Mark.hpp
)

set (lib_ui  ${SRC}/mainwindow.ui)
set (bin_src ${SRC}/main.cpp)

find_package (Qt5Widgets REQUIRED)
find_package (Qt5OpenGL REQUIRED)

qt5_wrap_cpp(lib_hdr_moc ${lib_hdr})
qt5_wrap_ui (lib_ui_moc  ${lib_ui})

include_directories (
        ${SRC}
        ${PROJECT_BINARY_DIR}/tests/integration-tests/qtApp
        ${PROJECT_SOURCE_DIR}/lib/include/
)

add_library (Lib SHARED
    ${lib_src}
    ${lib_hdr_moc}
    ${lib_ui_moc})

target_link_libraries (Lib
    Qt5::Widgets
    Qt5::OpenGL
    glRender
)

add_executable(qtApp ${bin_src})
target_link_libraries (qtApp Lib)

file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
