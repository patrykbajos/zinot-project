cmake_minimum_required(VERSION 3.5)
project(zinot-textool)

set(ZINOT_TEXTOOL_SRC
        zinot-textool/main.cpp
        zinot-textool/Application.cpp
        zinot-textool/convert/Converter.cpp
        zinot-textool/convert/ConverterFactory.cpp
        zinot-textool/convert/Mipmap.cpp
        zinot-textool/convert/PngConverter.cpp
        zinot-textool/convert/ZitexConverter.cpp
        zinot-textool/convert/PngLoader.cpp
        zinot-textool/config/ConfigDao.cpp
        zinot-textool/config/GlBindTextureDao.cpp
        zinot-textool/config/GlTexImageDao.cpp
        zinot-textool/config/GlTexParameterDao.cpp
        zinot-textool/config/LayersNamePatternsDao.cpp)
link_directories(./)

add_executable(zinot-textool ${ZINOT_TEXTOOL_SRC})

find_package(Qt5Core)
target_link_libraries(zinot-textool Qt5::Core)
target_link_libraries(zinot-textool zinot-utils)
target_link_libraries(zinot-textool FreeImage)
target_link_libraries(zinot-textool squish)
