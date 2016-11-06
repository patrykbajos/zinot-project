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

        ${PROJECT_SOURCE_DIR}/zitex/FileHeader.cpp
        ${PROJECT_SOURCE_DIR}/zitex/Writer.cpp
        ${PROJECT_SOURCE_DIR}/zitex/TexImageHeader.cpp
        ${PROJECT_SOURCE_DIR}/zitex/Reader.cpp

        ${PROJECT_SOURCE_DIR}/zimesh-json/JSONReader.cpp
        ${PROJECT_SOURCE_DIR}/zimesh-json/JSONData.cpp
        ${PROJECT_SOURCE_DIR}/zimesh-json/Material.cpp
        ${PROJECT_SOURCE_DIR}/zimesh-json/Mesh.cpp
        ${PROJECT_SOURCE_DIR}/zimesh-json/Object.cpp
        ${PROJECT_SOURCE_DIR}/zimesh-json/UvLayer.cpp)
link_directories(./)

add_library(zinot-utils SHARED ${ZINOT_UTILS_SRC})

find_package(Qt5Core)
target_link_libraries(zinot-utils Qt5::Core)