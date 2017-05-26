//
// Created by patryk on 30.08.16.
//

#ifndef ZINOT_PROJECT_SCENE_HPP
#define ZINOT_PROJECT_SCENE_HPP

#include <memory>
#include <zinot-engine/scene/GameObject.hpp>

namespace Zinot
{

class Engine;

class Scene
{
private:
   Engine * parentEngine;

   std::unique_ptr<GameObject> rootGameObject;
public:
   bool loadFromJsonFile(const QString & filePath);
};

}

#endif //ZINOT_PROJECT_SCENE_HPP
