cmake_minimum_required(VERSION 3.5)
project(zinot-textool)

set(PROJECT_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/zinot-textool")
set(ZINOT_TEXTOOL_SRC
        ${PROJECT_SOURCE_DIR}/main.cpp
        ${PROJECT_SOURCE_DIR}/Application.cpp
        ${PROJECT_SOURCE_DIR}/conv/Converter.cpp
        ${PROJECT_SOURCE_DIR}/conv/ConverterFactory.cpp
        ${PROJECT_SOURCE_DIR}/conv/Mipmap.cpp
        ${PROJECT_SOURCE_DIR}/conv/PngConverter.cpp
        ${PROJECT_SOURCE_DIR}/conv/ZitexConverter.cpp
        ${PROJECT_SOURCE_DIR}/conf/Configuration.cpp
        ${PROJECT_SOURCE_DIR}/conf/GlBindTexture.cpp
        ${PROJECT_SOURCE_DIR}/conf/GlTexImage.cpp
        ${PROJECT_SOURCE_DIR}/conf/GlTexParameter.cpp
        ${PROJECT_SOURCE_DIR}/conf/LayersNamePatterns.cpp
        )
link_directories(./)

add_executable(zinot-textool ${ZINOT_TEXTOOL_SRC})

find_package(Qt5Core)
target_link_libraries(zinot-textool zinot-utils)
target_link_libraries(zinot-textool freeimage)
target_link_libraries(zinot-textool squish)
target_link_libraries(zinot-textool Qt5::Core)