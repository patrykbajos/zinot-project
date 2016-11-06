//
// Created by patryk on 16.08.16.
//

#ifndef ZINOT_PROJECT_CAMERADAO_HPP
#define ZINOT_PROJECT_CAMERADAO_HPP

#include <QJsonObject>
#include <glm/glm.hpp>

namespace Zinot
{

class CameraDao
{
protected:
   bool valid = false;
   float fov;
   glm::vec3 pos;
   glm::vec2 rot;

   bool typesCheck(const QJsonObject & cameraObj);
   bool validCheck();
public:
   bool parseObject(const QJsonObject & cameraObj);

   bool isValid() const
   {
      return valid;
   }

   float getFov() const
   {
      return fov;
   }

   const glm::vec3 & getPos() const
   {
      return pos;
   }

   const glm::vec2 & getRot() const
   {
      return rot;
   }
};
}


#endif //ZINOT_PROJECT_CAMERADAO_HPP
