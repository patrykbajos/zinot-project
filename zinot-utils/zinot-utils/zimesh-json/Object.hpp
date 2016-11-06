//
// Created by patryk on 01.11.16.
//

#ifndef ZINOT_PROJECT_OBJECT_HPP
#define ZINOT_PROJECT_OBJECT_HPP

#include <QVector>
#include <QString>

namespace Zimesh
{

class Object
{
public:
   enum Type{
      Mesh
   };
private:
   Type type;
   QString data;
   QVector<float> matrix;
   QString parent;
};

}

#endif //ZINOT_PROJECT_OBJECT_HPP
