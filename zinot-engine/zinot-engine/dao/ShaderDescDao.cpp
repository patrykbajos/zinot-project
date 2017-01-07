//
// Created by patryk on 13.08.16.
//

#include "ShaderDescDao.hpp"
#include <QFile>

namespace Zinot
{
namespace ShaderDescKeys
{
const QString ShaderAttributesKey = "shaderAttributes";
const QString ShaderUniformsKey = "shaderUniforms";
const QString VertexShaderPathKey = "vertexShaderPath";
const QString FragmentShaderPathKey = "fragmentShaderPath";
}

bool ShaderDescDao::loadShdAttributes(const QJsonValue & attribsVal)
{
   if (!attribsVal.isObject())
      return false;
   QJsonObject attribsObj = attribsVal.toObject();

   for (QJsonObject::Iterator it = attribsObj.begin(); it != attribsObj.end(); ++it)
   {
      QString attrName = it.key();
      QJsonValueRef attrVal = it.value();

      loadShdAttribute(attrName, attrVal);
   }

   return true;
}

void ShaderDescDao::loadShdAttribute(const QString & attrName, const QJsonValue & attrVal)
{
   //TODO
}

bool ShaderDescDao::loadShdUniforms(const QJsonValue & uniformsVal)
{
   if (!uniformsVal.isObject())
      return false;
   QJsonObject uniformsObj = uniformsVal.toObject();

   for (QJsonObject::Iterator it = uniformsObj.begin(); it != uniformsObj.end(); ++it)
   {
      QString uniformName = it.key();
      QJsonValueRef uniformVal = it.value();

      loadShdUniform(uniformName, uniformVal);
   }

   return true;
}

void ShaderDescDao::loadShdUniform(const QString & uniformName, const QJsonValue & uniformVal)
{
   //TODO
}

bool ShaderDescDao::loadFromJsonVal(const QJsonValue & shdDescVal)
{
   if (!shdDescVal.isObject())
      return false;
   QJsonObject shdDescObj = shdDescVal.toObject();

   if (shdDescObj.contains(ShaderDescKeys::ShaderAttributesKey))
   {
      QJsonValue shdAttrVal = shdDescObj[ShaderDescKeys::ShaderAttributesKey];
      if (!loadShdAttributes(shdAttrVal))
         return false;
   } else
      shdAttributes.clear();

   if (shdDescObj.contains(ShaderDescKeys::ShaderUniformsKey))
   {
      QJsonValue shdUniVal = shdDescObj[ShaderDescKeys::ShaderUniformsKey];
      if (!loadShdUniforms(shdUniVal))
         return false;
   } else
      shdUnifroms.clear();

   vsPath = shdDescObj[ShaderDescKeys::VertexShaderPathKey].toString();
   fsPath = shdDescObj[ShaderDescKeys::FragmentShaderPathKey].toString();

   return true;
}
}