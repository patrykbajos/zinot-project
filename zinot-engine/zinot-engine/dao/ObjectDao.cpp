//
// Created by patryk on 13.08.16.
//

#include "ObjectDao.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Zinot
{

bool ObjectDao::parseObject(const QJsonObject & objectObj)
{
   if (!typesCheck(objectObj))
      return false;

   model = objectObj["model"].toString();
   shader = objectObj["shader"].toString();

   QJsonArray posArr = objectObj["pos"].toArray();
   pos = glm::vec3((float) posArr[0].toDouble(),
                   (float) posArr[1].toDouble(),
                   (float) posArr[2].toDouble());

   QJsonArray rotArr = objectObj["rot"].toArray();
   rot = glm::vec3((float) rotArr[0].toDouble(),
                   (float) rotArr[1].toDouble(),
                   (float) rotArr[2].toDouble());

   QJsonArray scaleArr = objectObj["scale"].toArray();
   scale = glm::vec3((float) scaleArr[0].toDouble(),
                     (float) scaleArr[1].toDouble(),
                     (float) scaleArr[2].toDouble());

   if (!validCheck())
      return false;

   valid = true;
   return true;
}

bool ObjectDao::typesCheck(const QJsonObject & objectObj)
{
   bool modelValid = objectObj["model"].isString();
   bool shaderValid = objectObj["shader"].isString();
   bool posValid = objectObj["pos"].isArray();
   bool rotValid = objectObj["rot"].isArray();
   bool scaleValid = objectObj["scale"].isArray();

   // Basic types valid
   if (!(modelValid && shaderValid && posValid && rotValid && scaleValid))
      return false;

   QJsonArray posArr = objectObj["pos"].toArray();
   QJsonArray rotArr = objectObj["rot"].toArray();
   QJsonArray scaleArr = objectObj["scale"].toArray();

   // Arrays size valid
   if (!((posArr.size() == 3) && (rotArr.size() == 3) && (scaleArr.size() == 3)))
      return false;

   // Arrays types valid
   for (uint32_t it = 0; it < 3; ++it)
   {
      if (!(posArr[it].isDouble() && rotArr[it].isDouble() && scaleArr[it].isDouble()))
         return false;
   }

   return true;
}

bool ObjectDao::validCheck()
{
   return !model.isEmpty() && !shader.isEmpty() && (scale != glm::vec3(0.0f, 0.0f, 0.0f));
}
}