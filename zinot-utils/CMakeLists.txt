cmake_minimum_required(VERSION 3.5)
project(zinot-utils)

find_package(Qt5Core)
link_directories(./)


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

        ${PROJECT_SOURCE_DIR}/zimesh-json/ZimeshJsonReader.cpp
        ${PROJECT_SOURCE_DIR}/zimesh-json/ZimeshJsonDao.cpp
        ${PROJECT_SOURCE_DIR}/zimesh-json/MaterialDao.cpp
        ${PROJECT_SOURCE_DIR}/zimesh-json/MeshDao.cpp
        ${PROJECT_SOURCE_DIR}/zimesh-json/ObjectDao.cpp
        ${PROJECT_SOURCE_DIR}/zimesh-json/UvLayerDao.cpp)
set(ZINOT_UTILS_TESTS
        tests/main.cpp
        tests/EndianTest.cpp
        tests/ZimeshJsonTest.cpp)

if (WIN32)
    include_directories(E:/dev/lib/FreeImage/Dist)
    link_directories(E:/dev/lib/FreeImage/Dist)     # Freeimage, dynamic
endif ()

add_library(zinot-utils SHARED ${ZINOT_UTILS_SRC})
target_link_libraries(zinot-utils Qt5::Core)
target_link_libraries(zinot-utils freeimage)

if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
    add_executable(zinot-utils-tests ${ZINOT_UTILS_TESTS})
    target_link_libraries(zinot-utils-tests zinot-utils)
    target_link_libraries(zinot-utils-tests gtest)
    target_link_libraries(zinot-utils-tests pthread)
endif ()