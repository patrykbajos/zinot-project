cmake_minimum_required(VERSION 3.5)
project(glloadgen)

set(GLLOADGEN_SRC gl_core_3_3.cpp)
include_directories(./)
add_library(glloadgen SHARED ${GLLOADGEN_SRC})

if (WIN32)
    target_link_libraries(glloadgen opengl32 glu32)
elseif (CMAKE_SYSTEM_NAME MATCHES "Linux")
    target_link_libraries(glloadgen GL GLU)
endif ()