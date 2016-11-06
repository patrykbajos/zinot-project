//
// Created by patryk on 13.08.16.
//

#include "ShaderDao.hpp"
#include <QFile>

namespace Zinot
{

bool ShaderDao::parseObject(const QJsonObject & shaderObj)
{
   if (!typesCheck(shaderObj))
      return false;

   name = shaderObj["name"].toString();
   vs = shaderObj["vs"].toString();
   fs = shaderObj["fs"].toString();

   if (!validCheck())
      return false;

   valid = true;
   return true;
}

bool ShaderDao::typesCheck(const QJsonObject & shaderObj)
{
   QJsonValue nameVal = shaderObj["name"];
   QJsonValue vsVal = shaderObj["vs"];
   QJsonValue fsVal = shaderObj["fs"];

   return nameVal.isString() && vsVal.isString() && fsVal.isString();
}

bool ShaderDao::validCheck()
{
   return !name.isEmpty() && QFile::exists(vs) && QFile::exists(fs);
}
}