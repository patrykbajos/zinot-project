//
// Created by patryk on 30.08.16.
//

#ifndef ZINOT_PROJECT_SCENE_HPP
#define ZINOT_PROJECT_SCENE_HPP

#include "GameObject.hpp"

namespace Zinot
{

class Scene
{
protected:

   GameObject * rootGameObject;
   QVector<GameObject *> gameObjects;
public:

};

}

#endif //ZINOT_PROJECT_SCENE_HPP
