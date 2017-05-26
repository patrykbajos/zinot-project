cmake_minimum_required(VERSION 3.5)
project(zinot-engine)

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
if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
    list(APPEND ZINOT_ENGINE_SRC ${ZINOT_ENGINE_TESTS})
endif ()
include_directories(./)


add_executable(zinot-engine ${ZINOT_ENGINE_SRC})

find_package(Qt5Core)
target_link_libraries(zinot-engine Qt5::Core)
target_link_libraries(zinot-engine ${GL_LIB_FILE} ${GLU_LIB_FILE} glloadgen)
target_link_libraries(zinot-engine zinot-utils)
target_link_libraries(zinot-engine freetype)
target_link_libraries(zinot-engine sfml-window sfml-graphics sfml-system)

target_link_libraries(zinot-engine debug gtest)
target_link_libraries(zinot-engine debug pthread)
