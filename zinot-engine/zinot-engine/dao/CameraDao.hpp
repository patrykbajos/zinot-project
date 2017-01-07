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
   float fov;
   float near;
   float far;
   glm::vec3 pos;
   glm::vec2 rot;

   bool loadPos(const QJsonValue & posVal);
   bool loadRot(const QJsonValue & rotVal);
public:
   bool loadFromJsonVal(const QJsonValue & camVal);
};
}


#endif //ZINOT_PROJECT_CAMERADAO_HPP
