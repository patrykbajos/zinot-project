cmake_minimum_required(VERSION 3.5)
project(zinot-textool)

set(PROJECT_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/zinot-textool")
set(ZINOT_TEXTOOL_SRC
        ${PROJECT_SOURCE_DIR}/main.cpp
        ${PROJECT_SOURCE_DIR}/Application.cpp
        ${PROJECT_SOURCE_DIR}/convert/Converter.cpp
        ${PROJECT_SOURCE_DIR}/convert/ConverterFactory.cpp
        ${PROJECT_SOURCE_DIR}/convert/Mipmap.cpp
        ${PROJECT_SOURCE_DIR}/convert/PngConverter.cpp
        ${PROJECT_SOURCE_DIR}/convert/ZitexConverter.cpp
        ${PROJECT_SOURCE_DIR}/convert/PngLoader.cpp
        ${PROJECT_SOURCE_DIR}/config/ConfigDao.cpp
        ${PROJECT_SOURCE_DIR}/config/GlBindTextureDao.cpp
        ${PROJECT_SOURCE_DIR}/config/GlTexImageDao.cpp
        ${PROJECT_SOURCE_DIR}/config/GlTexParameterDao.cpp
        ${PROJECT_SOURCE_DIR}/config/LayersNamePatternsDao.cpp
        )
link_directories(./)

add_executable(zinot-textool ${ZINOT_TEXTOOL_SRC})

find_package(Qt5Core)
target_link_libraries(zinot-textool zinot-utils)
target_link_libraries(zinot-textool freeimage)
target_link_libraries(zinot-textool squish)
target_link_libraries(zinot-textool Qt5::Core)