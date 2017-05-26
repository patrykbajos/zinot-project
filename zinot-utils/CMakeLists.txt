cmake_minimum_required(VERSION 3.5)
project(zinot-utils)

set(ZINOT_UTILS_SRC
        zinot-utils/unicode/Unicode.cpp
        zinot-utils/unicode/Utf32.cpp
        zinot-utils/unicode/Utf8.cpp
        zinot-utils/unicode/Utf16.cpp
        zinot-utils/Logger.cpp
        zinot-utils/Endian.cpp
        zinot-utils/Utf8String.cpp
        zinot-utils/zitex/FileHeader.cpp
        zinot-utils/zitex/Writer.cpp
        zinot-utils/zitex/TexImageHeader.cpp
        zinot-utils/zitex/Reader.cpp
        zinot-utils/json/JsonDao.cpp
        zinot-utils/json/JsonReader.cpp
        zinot-utils/zimesh-json/ZimeshJsonDao.cpp
        zinot-utils/zimesh-json/MaterialDao.cpp
        zinot-utils/zimesh-json/MeshDao.cpp
        zinot-utils/zimesh-json/ObjectDao.cpp
        zinot-utils/zimesh-json/UvLayerDao.cpp)
set(ZINOT_UTILS_TESTS
        tests/main.cpp
        tests/EndianTest.cpp
        tests/ZimeshJsonTest.cpp)
link_directories(./)

add_library(zinot-utils SHARED ${ZINOT_UTILS_SRC})
find_package(Qt5Core)
target_link_libraries(zinot-utils Qt5::Core)

if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
    add_executable(zinot-utils-tests ${ZINOT_UTILS_TESTS})
    target_link_libraries(zinot-utils-tests zinot-utils gtest pthread)
endif ()