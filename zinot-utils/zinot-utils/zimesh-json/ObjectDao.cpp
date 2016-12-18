//
// Created by patryk on 01.11.16.
//

#include "ObjectDao.hpp"

#include <QMap>
#include <QJsonArray>

namespace Zimesh
{
namespace ObjectKeys
{

static const QString TypeKey = "type";
static const QString DataKey = "data";
static const QString MatWorldKey = "matrixWorld";
static const QString ParentKey = "parent";
//static const QString Key = "";

}

bool ObjectDao::loadFromJsonValue(const QJsonValue & objectJsonVal)
{
   if (!objectJsonVal.isObject())
      return false;
   QJsonObject objectJsonObj = objectJsonVal.toObject();

   if (objectJsonObj.contains(ObjectKeys::TypeKey))
   {
      QJsonValue typeJsonVal = objectJsonObj[ObjectKeys::TypeKey];
      if (!loadType(typeJsonVal))
         return false;
   }

   if (objectJsonObj.contains(ObjectKeys::DataKey))
   {
      QJsonValue dataJsonVal = objectJsonObj[ObjectKeys::DataKey];
      if (!loadData(dataJsonVal))
         return false;
   }

   if (objectJsonObj.contains(ObjectKeys::ParentKey))
   {
      QJsonValue parentJsonVal = objectJsonObj[ObjectKeys::ParentKey];
      if (!loadParent(parentJsonVal))
         return false;
   }

   if (objectJsonObj.contains(ObjectKeys::MatWorldKey))
   {
      QJsonValue matWorldJsonVal = objectJsonObj[ObjectKeys::MatWorldKey];
      if (!loadMatWorld(matWorldJsonVal))
         return false;
   }

   return true;
}

ObjectDao::Type ObjectDao::getTypeFromString(const QString & typeName) const
{
   static QMap<QString, Type> typeMap{
      {"empty", Type::Empty},
      {"mesh",  Type::Mesh}
   };

   return typeMap.value(typeName, Type::Empty);
}

bool ObjectDao::loadType(const QJsonValue & typeJsonVal)
{
   if (!typeJsonVal.isString())
      return false;

   type = getTypeFromString(typeJsonVal.toString());
   return true;
}

bool ObjectDao::loadData(const QJsonValue & dataJsonVal)
{
   if (!dataJsonVal.isString())
      return false;

   data = dataJsonVal.toString();
   return true;
}

bool ObjectDao::loadMatWorld(const QJsonValue & matWorldJsonVal)
{
   if (!matWorldJsonVal.isArray())
      return false;

   QJsonArray matWorldJsonArr = matWorldJsonVal.toArray();
   const uint32_t mat4Size = (4 * 4);

   if (matWorldJsonArr.size() == mat4Size)
   {
      matrixWorld.resize(mat4Size);

      for (uint32_t it = 0; it < mat4Size; ++it)
         matrixWorld[it] = (float) matWorldJsonArr[it].toDouble(0.0);
   } else
   {
      return false;
   }

   return true;
}

bool ObjectDao::loadParent(const QJsonValue & parentJsonVal)
{
   if (!parentJsonVal.isString())
      return false;

   parent = parentJsonVal.toString();
   return true;
}
}