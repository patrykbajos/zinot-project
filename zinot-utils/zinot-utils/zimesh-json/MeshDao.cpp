//
// Created by patryk on 01.11.16.
//

#include "MeshDao.hpp"

#include <QJsonArray>

namespace Zimesh
{
namespace MeshKeys
{

static const QString facesGroupsKey = "facesGroups";
static const QString matSlotsKey = "materialSlots";
static const QString normalsKey = "normals";
static const QString uvLayersKey = "uvLayers";
static const QString verticesKey = "vertices";
//static const QString Key = "";

}

bool MeshDao::loadFromJsonValue(const QJsonValue & meshJsonVal)
{
   if (!meshJsonVal.isObject())
      return false;
   QJsonObject meshJsonObj = meshJsonVal.toObject();

   if (meshJsonObj.contains(MeshKeys::verticesKey))
   {
      QJsonValue verticesJsonVal = meshJsonObj[MeshKeys::verticesKey];
      if (!loadVertices(verticesJsonVal))
         return false;
   }

   if (meshJsonObj.contains(MeshKeys::normalsKey))
   {
      QJsonValue normalsJsonVal = meshJsonObj[MeshKeys::normalsKey];
      if (!loadNormals(normalsJsonVal))
         return false;
   }

   if (meshJsonObj.contains(MeshKeys::uvLayersKey))
   {
      QJsonValue uvLayersJsonVal = meshJsonObj[MeshKeys::uvLayersKey];
      if (!loadUvLayers(uvLayersJsonVal))
         return false;
   }

   if (meshJsonObj.contains(MeshKeys::matSlotsKey))
   {
      QJsonValue matSlotsVal = meshJsonObj[MeshKeys::matSlotsKey];
      if (!loadMatSlots(matSlotsVal))
         return false;
   }

   if (meshJsonObj.contains(MeshKeys::facesGroupsKey))
   {
      QJsonValue fgsJsonVal = meshJsonObj[MeshKeys::facesGroupsKey];
      if (!loadFacesGroups(fgsJsonVal))
         return false;
   }

   return true;
}

bool MeshDao::loadMatSlots(const QJsonValue & matSlotsVal)
{
   if (!matSlotsVal.isArray())
      return false;
   QJsonArray matSlotsArr = matSlotsVal.toArray();

   for (QJsonValue val : matSlotsArr)
   {
      if (val.isString())
         matSlots.append(val.toString());
   }

   return true;
}

bool MeshDao::loadFacesGroups(const QJsonValue & fgsJsonVal)
{
   if (!fgsJsonVal.isObject())
      return false;
   QJsonObject fgsJsonObj = fgsJsonVal.toObject();

   facesGroups.resize(fgsJsonObj.size());
   for (QJsonObject::Iterator it = fgsJsonObj.begin(); it == fgsJsonObj.end(); ++it)
   {
      // Get face group name (corresponding to id of material) and Json value
      QString fgName = it.key();
      QJsonValue fgJsonVal = it.value();

      loadFacesGroup(fgName, fgJsonVal);
   }

   return true;
}

void MeshDao::loadFacesGroup(const QString fgName, const QJsonValue fgJsonVal)
{
   if (!fgJsonVal.isArray())
      return;
   QJsonArray fgJsonArr = fgJsonVal.toArray();
   uint32_t fgId = fgName.toUInt();
   QVector<uint32_t> & fgVec = facesGroups[fgId];

   fgVec.reserve(fgJsonArr.size());
   for (QJsonValue fiJsonVal : fgJsonArr)
   {
      uint32_t fiUInt = (uint32_t) fiJsonVal.toInt();
      fgVec.append(fiUInt);
   }
   fgVec.squeeze();
}

bool MeshDao::loadVertices(const QJsonValue & verticesJsonVal)
{
   if (!verticesJsonVal.isArray())
      return false;
   QJsonArray verticesJsonArr = verticesJsonVal.toArray();

   vertices.reserve(verticesJsonArr.size());
   for (QJsonValue vertexJsonVal : verticesJsonArr)
   {
      float vertexComponent = (float) vertexJsonVal.toDouble();
      vertices.append(vertexComponent);
   }
   vertices.squeeze();

   return true;
}

bool MeshDao::loadNormals(const QJsonValue & normalsJsonVal)
{
   if (!normalsJsonVal.isArray())
      return false;
   QJsonArray normalsJsonArr = normalsJsonVal.toArray();

   normals.reserve(normalsJsonArr.size());
   for (QJsonValue normalJsonVal : normalsJsonArr)
   {
      float normalComponent = (float) normalJsonVal.toDouble();
      normals.append(normalComponent);
   }
   normals.squeeze();

   return true;
}

bool MeshDao::loadUvLayers(const QJsonValue & uvLayersJsonVal)
{
   if (!uvLayersJsonVal.isObject())
      return false;
   QJsonObject uvLayersJsonObj = uvLayersJsonVal.toObject();

   // Iterate through iterator. It gives possibility to get key.
   for (QJsonObject::Iterator it = uvLayersJsonObj.begin(); it == uvLayersJsonObj.end(); ++it)
   {
      QString uvLayerName = it.key();
      QJsonValue uvLayerJsonVal = it.value();

      uvLayers[uvLayerName] = UvLayerDao();
      uvLayers[uvLayerName].loadFromJsonValue(uvLayerJsonVal);
   }

   return true;
}
}