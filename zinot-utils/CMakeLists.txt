cmake_minimum_required(VERSION 3.5)
project(zinot-utils)

set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/zinot-utils)
set(ZINOT_UTILS_SRC
        ${PROJECT_SOURCE_DIR}/unicode/Unicode.cpp
        ${PROJECT_SOURCE_DIR}/unicode/Utf32.cpp
        ${PROJECT_SOURCE_DIR}/unicode/Utf8.cpp
        ${PROJECT_SOURCE_DIR}/unicode/Utf16.cpp
        ${PROJECT_SOURCE_DIR}/Logger.cpp
        ${PROJECT_SOURCE_DIR}/Endian.cpp
        ${PROJECT_SOURCE_DIR}/Utf8String.cpp
        ${PROJECT_SOURCE_DIR}/tex/Header.cpp
        ${PROJECT_SOURCE_DIR}/tex/Writer.cpp
        ${PROJECT_SOURCE_DIR}/tex/TexImageHeader.cpp
        ${PROJECT_SOURCE_DIR}/tex/Reader.cpp
        )
link_directories(./)

add_library(zinot-utils SHARED ${ZINOT_UTILS_SRC})

find_package(Qt5Core)
target_link_libraries(zinot-utils Qt5::Core)