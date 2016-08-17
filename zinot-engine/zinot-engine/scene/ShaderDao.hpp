//
// Created by patryk on 13.08.16.
//

#ifndef ZINOT_PROJECT_SHADERDAO_HPP
#define ZINOT_PROJECT_SHADERDAO_HPP

#include <QString>
#include <QJsonObject>

namespace Zinot
{

class ShaderDao
{
protected:
   bool valid = false;
   QString name, vs, fs;

   bool typesCheck(const QJsonObject & shaderObj);
   bool validCheck();
public:
   bool parseObject(const QJsonObject & shaderObj);

   bool isValid() const
   {
      return valid;
   }

   const QString & getName() const
   {
      return name;
   }

   void setName(const QString & name)
   {
      ShaderDao::name = name;
   }

   const QString & getVs() const
   {
      return vs;
   }

   void setVs(const QString & vs)
   {
      ShaderDao::vs = vs;
   }

   const QString & getFs() const
   {
      return fs;
   }

   void setFs(const QString & fs)
   {
      ShaderDao::fs = fs;
   }
};
}

#endif //ZINOT_PROJECT_SHADERDAO_HPP
