//
// Created by patryk on 13.05.16.
//
#include "../../../glloadgen/gl_core_3_3.hpp"
#include "FPSCamera.hpp"

#include <GL/glu.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Zinot
{
FPSCamera::FPSCamera() : rotation(0, 0), position(0, 0, 0), upVector(0, 1, 0)
{
   computeDirection();
}

void FPSCamera::computeDirection()
{
   float degToRad = (float) M_PI / 180;
   glm::vec2 rotInRad = rotation * degToRad;

   direction.z = -std::cos(rotInRad.y) * std::cos(rotInRad.x);
   direction.x = std::cos(rotInRad.y) * std::sin(rotInRad.x);
   direction.y = std::sin(rotInRad.y);
}

void FPSCamera::setVectorUp(const glm::vec3 & newUpVector)
{
   upVector = newUpVector;
}

void FPSCamera::setPosition(const glm::vec3 & newPosition)
{
   position = newPosition;
}

void FPSCamera::translate(const glm::vec3 & translation)
{
   position += translation;
}

void FPSCamera::addRotation(const glm::vec2 & value)
{
   rotation += value;
   computeDirection();
}

glm::mat4 FPSCamera::getMatrix()
{
   return glm::lookAt(position, direction + position, upVector);
}
}
