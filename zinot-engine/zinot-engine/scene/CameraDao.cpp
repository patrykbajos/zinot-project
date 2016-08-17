//
// Created by patryk on 16.08.16.
//

#include "CameraDao.hpp"

#include <QJsonArray>

namespace Zinot
{

bool CameraDao::parseObject(const QJsonObject & cameraObj)
{
   if (!typesCheck(cameraObj))
      return false;

   fov = (float) cameraObj["fov"].toDouble();

   QJsonArray posArr = cameraObj["pos"].toArray();
   pos = glm::vec3((float) posArr[0].toDouble(),
                   (float) posArr[1].toDouble(),
                   (float) posArr[2].toDouble());

   QJsonArray rotArr = cameraObj["rot"].toArray();
   rot = glm::vec2((float) rotArr[0].toDouble(),
                   (float) rotArr[1].toDouble());

   if (!validCheck())
      return false;

   valid = true;
   return true;
}

bool CameraDao::typesCheck(const QJsonObject & cameraObj)
{
   bool fovValid = cameraObj["fov"].isDouble();
   bool posValid = cameraObj["pos"].isArray();
   bool rotValid = cameraObj["rot"].isArray();

   // Basic types valid
   if (!(fovValid && posValid && rotValid))
      return false;

   QJsonArray posArr = cameraObj["pos"].toArray();
   QJsonArray rotArr = cameraObj["rot"].toArray();

   // Arrays size valid
   if ((posArr.size() != 3) || (rotArr.size() != 2))
      return false;

   // Arrays types valid
   for (uint32_t it = 0; it < 3; ++it)
   {
      if (!posArr[it].isDouble())
         return false;
   }
   for (uint32_t it = 0; it < 2; ++it)
   {
      if (!rotArr[it].isDouble())
         return false;
   }

   return true;
}

bool CameraDao::validCheck()
{
   return true;
}
}