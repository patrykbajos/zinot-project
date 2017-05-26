//
// Created by patryk on 12.01.17.
//

#include "Transform.hpp"

#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/transform.hpp>

namespace Zinot
{

Transform::Transform() : Component()
{
   setComponentType(Component::Type::Transform);
}

Transform::Transform(glm::vec3 position, glm::vec3 euler, glm::vec3 scale) : Transform()
{
   Transform::position = position;
   Transform::euler = euler;
   Transform::scale = scale;

   genTransformMat();
}

Transform::~Transform()
{
}

void Transform::genTransformMat()
{
   glm::mat4 transM = glm::translate(position);
   glm::mat4 rotM = glm::eulerAngleXYZ(euler.x, euler.y, euler.z);
   glm::mat4 scaleM = glm::scale(scale);

   transform = transM * scaleM * rotM;
}
}