//
// Created by patryk on 06.11.16.
//

#ifndef ZINOT_PROJECT_UVLAYER_HPP
#define ZINOT_PROJECT_UVLAYER_HPP

#include <QVector>
#include <QJsonValue>

namespace Zimesh
{

class UvLayerDao
{
private:
   QVector<float> uv;  // vec2 of u, v
   QVector<float> tan; // vec4 of x, y, z, bitangent sign
public:
   bool loadFromJsonValue(const QJsonValue & jsonVal);

   const QVector<float> & getUv() const
   {
      return uv;
   }

   const QVector<float> & getTan() const
   {
      return tan;
   }
};

}

#endif //ZINOT_PROJECT_UVLAYER_HPP
