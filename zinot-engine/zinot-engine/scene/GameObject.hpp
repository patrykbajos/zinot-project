//
// Created by patryk on 19.08.16.
//

#ifndef ZINOT_PROJECT_GAMEOBJECT_HPP
#define ZINOT_PROJECT_GAMEOBJECT_HPP

#include <zinot-engine/res-sys/MapResMgr.hpp>
#include <zinot-engine/res/GpuProgram.hpp>
#include <zinot-engine/res/Texture.hpp>
#include <zinot-engine/res/models/Model.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Zinot
{

class GameObject
{
protected:
   glm::vec3 pos;
   glm::quat orient;
   glm::vec3 scale;
   glm::mat4 transform;

   Model* model;

   QString name;
   GameObject* parent;
   QMap<QString, GameObject*> children;
public:
/* Metody TODO
 *
 * valid
 *
 * linkToParent
 * unlinkParent
 * linkChild
 * unlinkChild
 *
 * gettery/settery
 */
};

}

#endif //ZINOT_PROJECT_GAMEOBJECT_HPP
