cmake_minimum_required(VERSION 3.5)
project(zinot-project)

set(CMAKE_CXX_STANDARD 14)
include(Libraries.cmake)

include_directories(glloadgen)
include_directories(zinot-engine)
include_directories(zinot-textool)
include_directories(zinot-utils)

add_subdirectory(glloadgen)
add_subdirectory(zinot-utils)
add_subdirectory(zinot-textool)
add_subdirectory(zinot-engine)
