//
// Created by patryk on 01.11.16.
//

#ifndef ZINOT_PROJECT_MESH_HPP
#define ZINOT_PROJECT_MESH_HPP

#include <QVector>
#include <QString>
#include <QMap>

#include <zinot-utils/zimesh-json/UvLayer.hpp>

namespace Zimesh
{

class Mesh
{
private:
   QVector<QString> matSlots;
   QMap<uint32_t, QVector<uint32_t>> faces;

   QVector<float> vertices;
   QVector<float> normals;
   QMap<QString, UvLayer> uvLayers;
};

}

#endif //ZINOT_PROJECT_MESH_HPP
