cmake_minimum_required(VERSION 3.5)
project(zinot-engine)

set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/zinot-engine)
set(ZINOT_ENGINE_SRC
        zinot-engine/main.cpp
        zinot-engine/res/models/Material.cpp
        zinot-engine/res/models/Mesh.cpp
        zinot-engine/res/models/Model.cpp
        zinot-engine/res/GpuProgram.cpp
        zinot-engine/res/Texture.cpp
        zinot-engine/eng/Engine.cpp
        zinot-engine/eng/Window.cpp
        zinot-engine/eng/FPSCamera.cpp
        zinot-engine/res-sys/NamesRegister.cpp
        zinot-engine/res-sys/Resource.cpp
        zinot-engine/res-sys/MapResMgr.cpp
        zinot-engine/render/DeferredRenderer.cpp
        zinot-engine/scene/dao/SceneDao.cpp
        zinot-engine/scene/dao/ShaderDao.cpp
        zinot-engine/scene/dao/ShaderDao.hpp
        zinot-engine/scene/dao/ObjectDao.cpp
        zinot-engine/scene/dao/ObjectDao.hpp
        zinot-engine/scene/dao/CameraDao.cpp
        zinot-engine/scene/dao/CameraDao.hpp
        zinot-engine/scene/GameObject.cpp
        zinot-engine/scene/Scene.cpp
        )
set(ZINOT_ENGINE_TESTS
        tests/NamesRegisterTest.cpp
        tests/MapResMgrTest.cpp)
include_directories(./)

if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
    set(ZINOT_ENGINE_SRC ${ZINOT_ENGINE_SRC} ${ZINOT_ENGINE_TESTS})
endif ()

add_executable(zinot-engine ${ZINOT_ENGINE_SRC})

if (WIN32)
    include_directories(E:/dev/lib/SFML-2.1/include)
    link_directories(E:/dev/lib/SFML-2.1/lib)       # SFML, dynamic
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
target_link_libraries(zinot-engine zinot-utils)
target_link_libraries(zinot-engine sfml-window sfml-graphics sfml-system)
target_link_libraries(zinot-engine assimp)
target_link_libraries(zinot-engine glloadgen)

target_link_libraries(zinot-engine debug gtest)
target_link_libraries(zinot-engine debug pthread)
