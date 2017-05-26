

if (UNIX AND NOT APPLE)
    set(CMAKE_PREFIX_PATH "~/usr/lib/libQt5.7.0/5.7/gcc_64")
elseif (WIN32)
    set(CMAKE_PREFIX_PATH "E:/dev/lib/qt5.7.0/5.7/mingw53_32")
endif ()

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(LIB_FREEIMAGE_BIN CACHE PATH E:/dev/lib/libFreeImage/Dist/x32)
set(LIB_FREEIMAGE_INC CACHE PATH E:/dev/lib/libFreeImage/Dist/x32)
set(LIB_FREETYPE_BIN CACHE PATH E:/dev/lib/libfreetype-2.7/build)
set(LIB_FREETYPE_INC CACHE PATH E:/dev/lib/libfreetype-2.7/include)
set(LIB_GLM_INC CACHE PATH E:/dev/lib/libglm/include)
set(LIB_SQUISH_BIN CACHE PATH E:/dev/lib/libsquish-1.14/build)
set(LIB_SQUISH_INC CACHE PATH E:/dev/lib/libsquish-1.14/include)
set(LIB_SFML_BIN CACHE PATH E:/dev/lib/SFML-2.4.1/bin)
set(LIB_SFML_INC CACHE PATH E:/dev/lib/SFML-2.4.1/include)