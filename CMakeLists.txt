cmake_minimum_required(VERSION 3.5)
project(zinot-project)

if (UNIX AND NOT APPLE)
    set(CMAKE_PREFIX_PATH "/home/patryk/programy/Qt5.7.0/5.7/gcc_64")
elseif (WIN32)
    set(CMAKE_PREFIX_PATH "E:/dev/lib/qt5.7.0/5.7/mingw53_32")
endif ()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(glloadgen/src)
include_directories(zinot-engine)
include_directories(zinot-textool)
include_directories(zinot-utils)

add_subdirectory(glloadgen)
add_subdirectory(zinot-utils)
add_subdirectory(zinot-textool)
add_subdirectory(zinot-engine)
