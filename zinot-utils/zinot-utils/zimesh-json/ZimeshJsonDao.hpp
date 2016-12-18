//
// Created by patryk on 01.11.16.
//

#ifndef ZINOT_PROJECT_ZIMESHJSON_HPP
#define ZINOT_PROJECT_ZIMESHJSON_HPP

#include <QJsonObject>
#include <QJsonArray>
#include <QVector>
#include <QMap>
#include <QString>

#include <zinot-utils/zimesh-json/MaterialDao.hpp>
#include <zinot-utils/zimesh-json/MeshDao.hpp>
#include <zinot-utils/zimesh-json/ObjectDao.hpp>

namespace Zimesh
{

class ZimeshJsonDao
{
private:
   QVector<QString> depTex;
   QMap<QString, MaterialDao> materials;
   QMap<QString, MeshDao> meshes;
   QMap<QString, ObjectDao> objects;
public:
   bool loadFromJsonObject(const QJsonObject & jsonObject);

   const QVector<QString> & getDepTex() const
   {
      return depTex;
   }

   const QMap<QString, MaterialDao> & getMaterials() const
   {
      return materials;
   }

   const QMap<QString, MeshDao> & getMeshes() const
   {
      return meshes;
   }

   const QMap<QString, ObjectDao> & getObjects() const
   {
      return objects;
   }

private:
   bool loadDepTex(const QJsonValue & jsonVal);
   bool loadMaterials(const QJsonValue & jsonVal);
   bool loadMeshes(const QJsonValue & jsonVal);
   bool loadObjects(const QJsonValue & jsonVal);
};

}

#endif //ZINOT_PROJECT_ZIMESHJSON_HPP
