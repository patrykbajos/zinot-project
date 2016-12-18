//
// Created by patryk on 01.11.16.
//

#ifndef ZINOT_PROJECT_OBJECT_HPP
#define ZINOT_PROJECT_OBJECT_HPP

#include <QVector>
#include <QString>
#include <QJsonObject>

namespace Zimesh
{

class ObjectDao
{
public:
   enum Type{
      Mesh, Empty
   };
private:
   Type type;                    // Type of object
   QString data;                 // Data key assigned to scene object
   QVector<float> matrixWorld;   // Column major
   QString parent;               // Name of object parent

   bool loadType(const QJsonValue & typeJsonVal);
   bool loadData(const QJsonValue & dataJsonVal);
   bool loadMatWorld(const QJsonValue & matWorldJsonVal);
   bool loadParent(const QJsonValue & parentJsonVal);
   Type getTypeFromString(const QString & typeName) const;
public:
   bool loadFromJsonValue(const QJsonValue & objectJsonVal);

   Type getType() const
   {
      return type;
   }

   const QString & getData() const
   {
      return data;
   }

   const QVector<float> & getMatrixWorld() const
   {
      return matrixWorld;
   }

   const QString & getParent() const
   {
      return parent;
   }
};

}

#endif //ZINOT_PROJECT_OBJECT_HPP
