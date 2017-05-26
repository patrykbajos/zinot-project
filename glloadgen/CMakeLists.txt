cmake_minimum_required(VERSION 3.5)
project(glloadgen)

set(PROJECT_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(GLLOADGEN_SRC
    ${PROJECT_SOURCE_DIR}/gl_core_3_3.cpp
)
include_directories(${PROJECT_SOURCE_DIR})
add_library(glloadgen SHARED ${GLLOADGEN_SRC})

if (WIN32)
    target_link_libraries(glloadgen opengl32 glu32)
elseif (UNIX AND NOT APPLE)
    target_link_libraries(glloadgen GL GLU)
endif ()