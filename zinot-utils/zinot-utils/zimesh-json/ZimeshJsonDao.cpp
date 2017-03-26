//
// Created by patryk on 01.11.16.
//

#include "ZimeshJsonDao.hpp"

namespace Zimesh
{
namespace RootKeys
{

static const QString matsKey = "materials";
static const QString meshesKey = "meshes";
static const QString objectsKey = "objects";

}

bool ZimeshJsonDao::loadFromJsonDoc(const QJsonDocument & jsonDoc)
{
   if (!jsonDoc.isObject())
      return false;
   QJsonObject jsonObj = jsonDoc.object();

   if (jsonObj.contains(RootKeys::matsKey))
   {
      QJsonValue matsVal = jsonObj[RootKeys::matsKey];
      if (!loadMaterials(matsVal))
         return false;
   }
   if (jsonObj.contains(RootKeys::meshesKey))
   {
      QJsonValue meshesVal = jsonObj[RootKeys::meshesKey];
      if (!loadMeshes(meshesVal))
         return false;
   }
   if (jsonObj.contains(RootKeys::objectsKey))
   {
      QJsonValue objsVal = jsonObj[RootKeys::objectsKey];
      if (!loadObjects(objsVal))
         return false;
   }

   return true;
}

bool ZimeshJsonDao::loadMaterials(const QJsonValue & jsonVal)
{
   if (!jsonVal.isObject())
      return false;
   QJsonObject matsObj = jsonVal.toObject();

   for (QJsonObject::Iterator it = matsObj.begin(); it != matsObj.end(); ++it)
   {
      QString matName = it.key();
      QJsonValueRef matVal = it.value();

      MaterialDao & matDao = materials[matName];
      if (!matDao.loadFromJsonValue(matName, matVal))
         return false;
   }

   return true;
}

bool ZimeshJsonDao::loadMeshes(const QJsonValue & jsonVal)
{
   if (!jsonVal.isObject())
      return false;
   QJsonObject meshesObj = jsonVal.toObject();

   for (QJsonObject::Iterator it = meshesObj.begin(); it != meshesObj.end(); ++it)
   {
      QString meshName = it.key();
      QJsonValueRef meshVal = it.value();

      MeshDao & meshDao = meshes[meshName];
      if (!meshDao.loadFromJsonValue(meshName, meshVal))
         return false;
   }

   return true;
}

bool ZimeshJsonDao::loadObjects(const QJsonValue & jsonVal)
{
   if (!jsonVal.isObject())
      return false;
   QJsonObject objectsObj = jsonVal.toObject();

   for (QJsonObject::Iterator it = objectsObj.begin(); it != objectsObj.end(); ++it)
   {
      QString objectName = it.key();
      QJsonValueRef objectVal = it.value();

      ObjectDao & objectDao = objects[objectName];
      if (!objectDao.loadFromJsonValue(objectName, objectVal))
         return false;
   }

   return true;
}
}