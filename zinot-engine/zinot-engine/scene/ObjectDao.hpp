//
// Created by patryk on 13.08.16.
//

#ifndef ZINOT_PROJECT_OBJECTDAO_HPP
#define ZINOT_PROJECT_OBJECTDAO_HPP

#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <glm/glm.hpp>

namespace Zinot
{

class ObjectDao
{
protected:
   bool valid = false;
   QString model, shader;
   glm::vec3 pos;
   glm::vec3 rot;
   glm::vec3 scale;

   bool typesCheck(const QJsonObject & objectObj);
   bool validCheck();
public:
   bool parseObject(const QJsonObject & objectObj);

   bool isValid() const
   {
      return valid;
   }

   const QString & getModel() const
   {
      return model;
   }

   const QString & getShader() const
   {
      return shader;
   }

   const glm::vec3 & getPos() const
   {
      return pos;
   }

   const glm::vec3 & getRot() const
   {
      return rot;
   }

   const glm::vec3 & getScale() const
   {
      return scale;
   }
};
}

#endif //ZINOT_PROJECT_OBJECTDAO_HPP
