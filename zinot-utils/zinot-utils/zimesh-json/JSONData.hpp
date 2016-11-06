//
// Created by patryk on 01.11.16.
//

#ifndef ZINOT_PROJECT_ZIMESHJSON_HPP
#define ZINOT_PROJECT_ZIMESHJSON_HPP

#include <QJsonObject>
#include <QVector>
#include <QMap>
#include <QString>

#include <zinot-utils/zimesh-json/Material.hpp>
#include <zinot-utils/zimesh-json/Mesh.hpp>
#include <zinot-utils/zimesh-json/Object.hpp>

namespace Zimesh
{

class JSONData
{
private:
   QVector<QString> depTex;
   QMap<QString, Material> mat;
   QMap<QString, Mesh> meshes;
   QMap<QString, Object> obj;
public:
   bool loadFromJSONObject(const QJsonObject & jsonObject);
};

}

#endif //ZINOT_PROJECT_ZIMESHJSON_HPP
