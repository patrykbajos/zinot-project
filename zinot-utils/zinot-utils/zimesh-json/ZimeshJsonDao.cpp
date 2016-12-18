//
// Created by patryk on 01.11.16.
//

#include "ZimeshJsonDao.hpp"

namespace Zimesh
{
namespace RootKeys
{

static const QString depTexKey = "dependentTextures";
static const QString matsKey = "materials";
static const QString meshesKey = "meshes";
static const QString objectsKey = "objects";
}

bool ZimeshJsonDao::loadFromJsonObject(const QJsonObject & jsonObject)
{
   if (jsonObject.contains(RootKeys::depTexKey))
   {
      QJsonValue depTexVal = jsonObject[RootKeys::depTexKey];
      if (!loadDepTex(depTexVal))
         return false;
   }
   if (jsonObject.contains(RootKeys::matsKey))
   {
      QJsonValue matsVal = jsonObject[RootKeys::matsKey];
      if (!loadMaterials(matsVal))
         return false;
   }
   if (jsonObject.contains(RootKeys::meshesKey))
   {
      QJsonValue meshesVal = jsonObject[RootKeys::meshesKey];
      if (!loadMeshes(meshesVal))
         return false;
   }
   if (jsonObject.contains(RootKeys::objectsKey))
   {
      QJsonValue objsVal = jsonObject[RootKeys::objectsKey];
      if (!loadObjects(objsVal))
         return false;
   }

   return true;
}

bool ZimeshJsonDao::loadDepTex(const QJsonValue & jsonVal)
{
   if (!jsonVal.isArray())
      return false;

   QJsonArray depTexArr = jsonVal.toArray();

   for (QJsonValue val : depTexArr)
   {
      if (val.isString())
         depTex.push_back(val.toString());
   }

   return true;
}

bool ZimeshJsonDao::loadMaterials(const QJsonValue & jsonVal)
{
   if (!jsonVal.isObject())
      return false;
   QJsonObject matsObj = jsonVal.toObject();

   for (QJsonObject::ConstIterator it = matsObj.begin(); it == matsObj.end(); ++it)
   {
      QJsonValue matVal = it.value();
      QString key = it.key();

      if (!matVal.isObject())
         continue;

      materials[key] = MaterialDao();
      materials[key].loadFromJsonValue(matVal.toObject());
   }

   return true;
}

bool ZimeshJsonDao::loadMeshes(const QJsonValue & jsonVal)
{
   if (!jsonVal.isObject())
      return false;
   QJsonObject meshesObj = jsonVal.toObject();

   for (QJsonObject::ConstIterator it = meshesObj.begin(); it == meshesObj.end(); ++it)
   {
      QJsonValue meshVal = it.value();
      QString key = it.key();
      if (!meshVal.isObject())
         continue;

      meshes[key] = MeshDao();
      meshes[key].loadFromJsonValue(meshVal.toObject());
   }

   return true;
}

bool ZimeshJsonDao::loadObjects(const QJsonValue & jsonVal)
{
   if (!jsonVal.isObject())
      return false;
   QJsonObject objectsObj = jsonVal.toObject();

   for (QJsonObject::ConstIterator it = objectsObj.begin(); it == objectsObj.end(); ++it)
   {
      QJsonValue objectVal = it.value();
      QString key = it.key();
      if (!objectVal.isObject())
         continue;

      objects[key] = ObjectDao();
      objects[key].loadFromJsonValue(objectVal.toObject());
   }

   return true;
}
}