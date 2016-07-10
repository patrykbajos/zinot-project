//
// Created by patryk on 13.05.16.
//

#ifndef ZINOTENGINEPROJECT_FPSCAMERA_HPP
#define ZINOTENGINEPROJECT_FPSCAMERA_HPP

#include <glm/glm.hpp>

namespace Zinot
{
class FPSCamera
{
protected:
   glm::vec2 rotation;
   glm::vec3 position;
   glm::vec3 direction;
   glm::vec3 upVector;

   void computeDirection();
public:
   FPSCamera();
   void setVectorUp(const glm::vec3 & newUpVector);
   void setPosition(const glm::vec3 & newPosition);
   void translate(const glm::vec3 & translation);
   void addRotation(const glm::vec2 & value);
   glm::mat4 getMatrix();

   inline const glm::vec3 & getDirection() const
   {
      return direction;
   }

   inline const glm::vec3 & getUpVector() const
   {
      return upVector;
   }
};
}

#endif //ZINOTENGINEPROJECT_FPSCAMERA_HPP
