//
// Created by patryk on 06.11.16.
//

#ifndef ZINOT_PROJECT_UVLAYER_HPP
#define ZINOT_PROJECT_UVLAYER_HPP

#include <QVector>

namespace Zimesh
{

class UvLayer
{
private:
   QVector<float> uv;
   QVector<float> tangent;
   QVector<float> bitangent;
};

}

#endif //ZINOT_PROJECT_UVLAYER_HPP
