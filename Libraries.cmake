#####
# Configuration file.
# User must replace directories to own.
#####

if (CMAKE_SYSTEM_NAME MATCHES "Linux")
    set(LIB_QT_HOME "~/usr/lib/libQt5.7.0/5.7/gcc_64" CACHE PATH "Qt5 home dir.")
    list(APPEND CMAKE_PREFIX_PATH ${LIB_QT_HOME})

    set(GL_LIB_FILE GL CACHE STRING "OpenGL library file name.")
    set(GLU_LIB_FILE GLU CACHE STRING "OpenGL Utility library file name.")
elseif (WIN32)
    set(LIB_QT_HOME "E:/dev/lib/libQt571/5.7/mingw53_32" CACHE PATH "Qt5 home dir.")
    list(APPEND CMAKE_PREFIX_PATH ${LIB_QT_HOME})

    set(LIB_FREEIMAGE_LIB E:/dev/lib/libFreeImage/Dist/x32 CACHE PATH "")
    set(LIB_FREEIMAGE_INC E:/dev/lib/libFreeImage/Dist/x32 CACHE PATH "")
    set(LIB_FREETYPE_LIB E:/dev/lib/libfreetype-2.7/build CACHE PATH "")
    set(LIB_FREETYPE_INC E:/dev/lib/libfreetype-2.7/include CACHE PATH "")
    set(LIB_GLM_INC E:/dev/lib/libglm/include CACHE PATH "")
    set(LIB_SQUISH_LIB E:/dev/lib/libsquish-1.14/build CACHE PATH "")
    set(LIB_SQUISH_INC E:/dev/lib/libsquish-1.14/include CACHE PATH "")
    set(LIB_SFML_LIB E:/dev/lib/SFML-2.4.1/bin CACHE PATH "")
    set(LIB_SFML_INC E:/dev/lib/SFML-2.4.1/include CACHE PATH "")

    include_directories(${LIB_FREEIMAGE_INC} ${LIB_FREETYPE_INC} ${LIB_GLM_INC} ${LIB_SQUISH_INC} ${LIB_SFML_INC})
    link_directories(${LIB_FREEIMAGE_LIB} ${LIB_FREETYPE_LIB} ${LIB_SQUISH_LIB} ${LIB_SFML_LIB})

    set(GL_LIB_FILE opengl32 CACHE STRING "OpenGL library file name.")
    set(GLU_LIB_FILE glu32 CACHE STRING "OpenGL Utility library file name.")
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

