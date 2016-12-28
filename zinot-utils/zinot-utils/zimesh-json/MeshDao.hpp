//
// Created by patryk on 01.11.16.
//

#ifndef ZINOT_PROJECT_MESH_HPP
#define ZINOT_PROJECT_MESH_HPP

#include <QVector>
#include <QString>
#include <QMap>
#include <QJsonObject>

#include <zinot-utils/zimesh-json/UvLayerDao.hpp>

namespace Zimesh
{

class MeshDao
{
private:
   QString name;
   QVector<QString> matSlots;
   QVector<QVector<uint32_t>> facesGroups;

   QVector<float> vertices;
   QVector<float> normals;
   QMap<QString, UvLayerDao> uvLayers;

   bool loadMatSlots(const QJsonValue & matSlotsVal);
   bool loadFacesGroups(const QJsonValue & fgsJsonVal);
   void loadFacesGroup(const QString fgName, const QJsonValue fgJsonVal);
   bool loadVertices(const QJsonValue & verticesJsonVal);
   bool loadNormals(const QJsonValue & normalsJsonVal);
   bool loadUvLayers(const QJsonValue & uvLayersJsonVal);
public:
   bool loadFromJsonValue(const QString & meshName, const QJsonValue & meshJsonVal);

   const QVector<QString> & getMatSlots() const
   {
      return matSlots;
   }

   const QVector<QVector<uint32_t>> & getFacesGroups() const
   {
      return facesGroups;
   }

   const QVector<float> & getVertices() const
   {
      return vertices;
   }

   const QVector<float> & getNormals() const
   {
      return normals;
   }

   const QMap<QString, UvLayerDao> & getUvLayers() const
   {
      return uvLayers;
   }
};

}

#endif //ZINOT_PROJECT_MESH_HPP
