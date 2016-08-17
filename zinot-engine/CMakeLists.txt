cmake_minimum_required(VERSION 3.5)
project(zinot-engine)

set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/zinot-engine)
set(ZINOT_ENGINE_SRC_MAIN
        ${PROJECT_SOURCE_DIR}/main.cpp
        ${PROJECT_SOURCE_DIR}/res/models/ModelNode.cpp
        ${PROJECT_SOURCE_DIR}/res/models/Material.cpp
        ${PROJECT_SOURCE_DIR}/res/models/Mesh.cpp
        ${PROJECT_SOURCE_DIR}/res/models/Model.cpp
        ${PROJECT_SOURCE_DIR}/res/GpuProgram.cpp
        ${PROJECT_SOURCE_DIR}/res/Texture.cpp
        ${PROJECT_SOURCE_DIR}/res/Shader.cpp
        ${PROJECT_SOURCE_DIR}/eng/Engine.cpp
        ${PROJECT_SOURCE_DIR}/eng/Window.cpp
        ${PROJECT_SOURCE_DIR}/eng/FPSCamera.cpp
        ${PROJECT_SOURCE_DIR}/res-sys/NamesRegister.cpp
        ${PROJECT_SOURCE_DIR}/res-sys/Resource.cpp
        ${PROJECT_SOURCE_DIR}/render/DeferredRenderer.cpp
        ${PROJECT_SOURCE_DIR}/scene/Scene.cpp
        ${PROJECT_SOURCE_DIR}/res-sys/MapResMgr.cpp zinot-engine/scene/ShaderDao.cpp zinot-engine/scene/ShaderDao.hpp zinot-engine/scene/ObjectDao.cpp zinot-engine/scene/ObjectDao.hpp zinot-engine/scene/CameraDao.cpp zinot-engine/scene/CameraDao.hpp)
set(ZINOT_ENGINE_SRC_TESTS
        tests/NamesRegisterTest.cpp
        tests/MapResMgrTest.cpp)
include_directories(./)

if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
    set(ZINOT_ENGINE_SRC ${ZINOT_ENGINE_SRC_MAIN} ${ZINOT_ENGINE_SRC_TESTS})
else ()
    set(ZINOT_ENGINE_SRC ${ZINOT_ENGINE_SRC_MAIN})
endif ()

add_executable(zinot-engine ${ZINOT_ENGINE_SRC})

if (WIN32)
    include_directories(E:/dev/lib/SFML-2.1/include)
    link_directories(E:/dev/lib/SFML-2.1/lib)       # SFML, dynamic
    include_directories(E:/dev/lib/FreeImage/Dist)
    link_directories(E:/dev/lib/FreeImage/Dist)     # Freeimage, dynamic
    include_directories(E:/dev/lib/freetype-2.6.3/include)
    link_directories(E:/dev/lib/freetype-2.6.3/objs/vc2010/Win32) # FreeType2, dynamic
    include_directories(/media/patryk/Gry/dev/lib/libsquish-1.13/include)
    link_directories(E:/dev/lib/libsquish-1.13/Release) # Libsquish, linked statically
    include_directories(E:/dev/lib/glm-0.9.7.5/glm) # glm

    target_link_libraries(zinot-engine gl glu)
    target_link_libraries(zinot-engine freetype263)
endif ()

if (UNIX AND NOT APPLE)
    target_link_libraries(zinot-engine GL GLU)
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

target_link_libraries(zinot-engine debug gtest)
target_link_libraries(zinot-engine debug pthread)
