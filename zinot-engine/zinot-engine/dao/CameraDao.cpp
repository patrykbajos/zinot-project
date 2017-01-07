//
// Created by patryk on 16.08.16.
//

#include "CameraDao.hpp"

#include <QJsonArray>

namespace Zinot
{

namespace CameraKeys
{
const QString fovKey = "fov";
const QString nearKey = "near";
const QString farKey = "far";
const QString posKey = "pos";
const QString rotKey = "rot";
}

bool CameraDao::loadFromJsonVal(const QJsonValue & camVal)
{
   if (!camVal.isObject())
      return false;
   QJsonObject camObj = camVal.toObject();

   if (camObj.contains(CameraKeys::fovKey))
   {
      QJsonValue fovVal = camObj[CameraKeys::fovKey];
      fov = (float) fovVal.toDouble(70.0);
   } else
      fov = 70.0f;

   if (camObj.contains(CameraKeys::nearKey))
   {
      QJsonValue nearVal = camObj[CameraKeys::nearKey];
      near = (float) nearVal.toDouble(0.1);
   } else
      near = 0.1f;

   if (camObj.contains(CameraKeys::farKey))
   {
      QJsonValue farVal = camObj[CameraKeys::farKey];
      far = (float) farVal.toDouble(100.0);
   } else
      far = 100.0f;

   if (camObj.contains(CameraKeys::posKey))
   {
      QJsonValue posVal = camObj[CameraKeys::posKey];
      if (!loadPos(posVal))
         return false;
   } else
      pos = glm::vec3(0.0f, 0.0f, 0.0f);

   if (camObj.contains(CameraKeys::rotKey))
   {
      QJsonValue rotVal = camObj[CameraKeys::rotKey];
      if (!loadRot(rotVal))
         return false;
   } else
      rot = glm::vec2(0.0f, 0.0f);

   return true;
}

bool CameraDao::loadPos(const QJsonValue & posVal)
{
   if (!posVal.isArray())
      return false;
   QJsonArray posArr = posVal.toArray();

   if (posArr.size() != 3)
      return false;

   pos.x = (float) posArr[0].toDouble(0.0);
   pos.y = (float) posArr[1].toDouble(0.0);
   pos.z = (float) posArr[2].toDouble(0.0);

   return true;
}

bool CameraDao::loadRot(const QJsonValue & rotVal)
{
   if (!rotVal.isArray())
      return false;
   QJsonArray rotArr = rotVal.toArray();

   if (rotArr.size() != 2)
      return false;

   rot.x = (float) rotArr[0].toDouble(0.0);
   rot.y = (float) rotArr[1].toDouble(0.0);

   return true;
}
}