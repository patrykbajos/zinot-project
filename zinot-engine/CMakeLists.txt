cmake_minimum_required(VERSION 3.5)
project(zinot-engine)

set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/zinot-engine)
set(ZINOT_ENGINE_SRC
        ${PROJECT_SOURCE_DIR}/main.cpp
        ${PROJECT_SOURCE_DIR}/engine/Viewport.cpp
        ${PROJECT_SOURCE_DIR}/engine/resources/models/ModelNode.cpp
        ${PROJECT_SOURCE_DIR}/engine/resources/models/Material.cpp
        ${PROJECT_SOURCE_DIR}/engine/resources/models/Mesh.cpp
        ${PROJECT_SOURCE_DIR}/engine/resources/models/Model.cpp
        ${PROJECT_SOURCE_DIR}/engine/resources/GpuProgram.cpp
        ${PROJECT_SOURCE_DIR}/engine/resources/Texture.cpp
        ${PROJECT_SOURCE_DIR}/engine/resources/Shader.cpp
        ${PROJECT_SOURCE_DIR}/engine/Engine.cpp
        ${PROJECT_SOURCE_DIR}/engine/Window.cpp
        ${PROJECT_SOURCE_DIR}/engine/FPSCamera.cpp
        ${PROJECT_SOURCE_DIR}/resources/MapResMgr.cpp
        ${PROJECT_SOURCE_DIR}/resources/NamesRegister.cpp
        ${PROJECT_SOURCE_DIR}/resources/Resource.cpp
        )
include_directories(./)

add_executable(zinot-engine ${ZINOT_ENGINE_SRC})

if (WIN32)
    include_directories(E:/dev/lib/SFML-2.1/include)
    link_directories(E:/dev/lib/SFML-2.1/lib)       # SFML, dynamic
    include_directories(E:/dev/lib/FreeImage/Dist)
    link_directories(E:/dev/lib/FreeImage/Dist)     # Freeimage, dynamic
    include_directories(E:/dev/lib/freetype-2.6.3/include)
    link_directories(E:/dev/lib/freetype-2.6.3/objs/vc2010/Win32) # FreeType2, dynamic
    include_directories(E:/dev/lib/glew-1.10.0/include)
    link_directories(E:/dev/lib/glew-1.10.0/lib/Release/Win32) # GLEW
    include_directories(/media/patryk/Gry/dev/lib/libsquish-1.13/include)
    link_directories(E:/dev/lib/libsquish-1.13/Release) # Libsquish, linked statically
    include_directories(E:/dev/lib/glm-0.9.7.5/glm) # glm

    target_link_libraries(zinot-engine gl glu glew32)
    target_link_libraries(zinot-engine freetype263)
endif ()

if (UNIX AND NOT APPLE)
    target_link_libraries(zinot-engine GL GLU GLEW)
    include_directories(/usr/include/freetype2)
    target_link_libraries(zinot-engine freetype)
endif ()

find_package(Qt5Core)
target_link_libraries(zinot-engine Qt5::Core)
target_link_libraries(zinot-engine sfml-window sfml-graphics sfml-system)
target_link_libraries(zinot-engine assimp)
target_link_libraries(zinot-engine freeimage)
target_link_libraries(zinot-engine zinot-utils)
target_link_libraries(zinot-engine glloadgen)
