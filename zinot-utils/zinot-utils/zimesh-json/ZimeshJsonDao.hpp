//
// Created by patryk on 01.11.16.
//

#ifndef ZINOT_PROJECT_ZIMESHJSON_HPP
#define ZINOT_PROJECT_ZIMESHJSON_HPP

#include <zinot-utils/json/JsonDao.hpp>
#include <zinot-utils/zimesh-json/MaterialDao.hpp>
#include <zinot-utils/zimesh-json/MeshDao.hpp>
#include <zinot-utils/zimesh-json/ObjectDao.hpp>

#include <QJsonObject>
#include <QJsonArray>
#include <QVector>
#include <QMap>
#include <QString>

namespace Zimesh
{

class ZimeshJsonDao : public JsonDao
{
private:
   QMap<QString, MaterialDao> materials;
   QMap<QString, MeshDao> meshes;
   QMap<QString, ObjectDao> objects;
public:
   virtual bool loadFromJsonDoc(const QJsonDocument & jsonDoc) override;

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
   bool loadMaterials(const QJsonValue & jsonVal);
   bool loadMeshes(const QJsonValue & jsonVal);
   bool loadObjects(const QJsonValue & jsonVal);
};

}

#endif //ZINOT_PROJECT_ZIMESHJSON_HPP
