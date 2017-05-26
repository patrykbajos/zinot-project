//
// Created by patryk on 12.01.17.
//

#ifndef ZINOT_PROJECT_TRANSFORM_HPP
#define ZINOT_PROJECT_TRANSFORM_HPP

#include <glm/glm.hpp>

#include <zinot-engine/scene/components/Component.hpp>

namespace Zinot
{

class Transform : public Component
{
private:
   glm::vec3 position;
   glm::vec3 euler;
   glm::vec3 scale;
   glm::mat4 transform;

   void genTransformMat();
public:
   Transform();
   Transform(glm::vec3 position, glm::vec3 euler, glm::vec3 scale);
   virtual ~Transform() override;
};
}

#endif //ZINOT_PROJECT_TRANSFORM_HPP
