cmake_minimum_required(VERSION 3.5)
project(zinot-engine)

set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/zinot-engine)
set(ZINOT_ENGINE_SRC
        zinot-engine/main.cpp
        zinot-engine/res/models/Material.cpp
        zinot-engine/res/models/Model.cpp
        zinot-engine/res/Shader.cpp
        zinot-engine/res/Texture.cpp
        zinot-engine/eng/Engine.cpp
        zinot-engine/eng/Window.cpp
        zinot-engine/eng/FPSCamera.cpp
        zinot-engine/res-sys/NamesRegister.cpp
        zinot-engine/res-sys/Resource.cpp
        zinot-engine/res-sys/MapResMgr.cpp
        zinot-engine/render/DeferredRenderer.cpp
        zinot-engine/dao/SceneDao.cpp
        zinot-engine/dao/ShaderDescDao.cpp
        zinot-engine/dao/ObjectDao.cpp
        zinot-engine/dao/CameraDao.cpp
        zinot-engine/scene/GameObject.cpp
        zinot-engine/scene/Scene.cpp
        zinot-engine/scene/components/Component.cpp
        zinot-engine/scene/components/Transform.cpp
        zinot-engine/eng/ResMgrList.cpp
        zinot-engine/scene/components/ModelRenderer.cpp
        )
set(ZINOT_ENGINE_TESTS
        tests/NamesRegisterTest.cpp
        tests/ShaderDescDaoTest.cpp
        tests/MapResMgrTest.cpp)
include_directories(./)

if(WIN32)
    include_directories(E:/dev/lib/SFML-2.4.1/include)
    link_directories(E:/dev/lib/SFML-2.4.1/lib)
    include_directories(E:/dev/lib/libfreetype-2.7/include)
    link_directories(E:/dev/lib/libfreetype-2.7/build)
    include_directories(E:/dev/lib/libsquish-1.14/include)
    link_directories(E:/dev/lib/libsquish-1.14/build)
    include_directories(E:/dev/lib/libglm/include)
elseif(UNIX AND NOT APPLE)
    include_directories(/usr/include/freetype2)
endif()

if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
    set(ZINOT_ENGINE_SRC ${ZINOT_ENGINE_SRC} ${ZINOT_ENGINE_TESTS})
endif ()

add_executable(zinot-engine ${ZINOT_ENGINE_SRC})

if(WIN32)
    target_link_libraries(zinot-engine opengl32 glu32)
elseif(UNIX AND NOT APPLE)
    target_link_libraries(zinot-engine GL GLU)
endif()

find_package(Qt5Core)
target_link_libraries(zinot-engine Qt5::Core)
target_link_libraries(zinot-engine zinot-utils)
target_link_libraries(zinot-engine freetype)
target_link_libraries(zinot-engine sfml-window sfml-graphics sfml-system)
target_link_libraries(zinot-engine glloadgen)

target_link_libraries(zinot-engine debug gtest)
target_link_libraries(zinot-engine debug pthread)
