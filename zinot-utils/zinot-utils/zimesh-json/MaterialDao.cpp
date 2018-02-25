//
// Created by patryk on 01.11.16.
//

#include "MaterialDao.hpp"

#include <QJsonArray>

namespace Zimesh
{
namespace MaterialKeys
{

static const QString drawableKey = "drawable";
static const QString shaderPathKey = "shaderPath";
static const QString shaderUniformsKey = "shaderUniforms";
static const QString shaderAttributesKey = "shaderAttributes";
static const QString envprobeTypeKey = "envprobeType";
static const QString renderPassKey = "renderPass";
static const QString lightingModelKey = "lightingModel";

}

bool MaterialDao::loadFromJsonValue(const QString & matName, const QJsonValue & matVal)
{
   if (!matVal.isObject())
      return false;
   QJsonObject matObj = matVal.toObject();

   name = matName;
   drawable = matObj[MaterialKeys::drawableKey].toBool(true);
   shaderPath = matObj[MaterialKeys::shaderPathKey].toString();

   if (matObj.contains(MaterialKeys::shaderAttributesKey))
   {
      QJsonValue shaderAttrVal = matObj[MaterialKeys::shaderAttributesKey];
      if (!loadShaderAttributes(shaderAttrVal))
         return false;
   } else
   {
      shaderAttributes.clear();
   }

   if (matObj.contains(MaterialKeys::shaderUniformsKey))
   {
      QJsonValue shaderUniVal = matObj[MaterialKeys::shaderUniformsKey];
      if (!loadShaderUniforms(shaderUniVal))
         return false;
   } else
   {
      shaderUniforms.clear();
   }

   if (matObj.contains(MaterialKeys::envprobeTypeKey))
   {
      QJsonValue envprobeVal = matObj[MaterialKeys::envprobeTypeKey];
      if (!loadEnvprobeType(envprobeVal))
         return false;
   } else
   {
      envprobeType = EnvprobeType::None;
   }

   if (matObj.contains(MaterialKeys::renderPassKey))
   {
      QJsonValue renderPassVal = matObj[MaterialKeys::renderPassKey];
      if (!loadRenderPass(renderPassVal))
         return false;
   } else
   {
      renderPass = RenderPass::Deferred;
   }

   if (matObj.contains(MaterialKeys::lightingModelKey))
   {
      QJsonValue lightingMdlVal = matObj[MaterialKeys::lightingModelKey];
      if (!loadLightingModel(lightingMdlVal))
         return false;
   } else
   {
      lightingModel = "Default";
   }

   return true;
}

bool MaterialDao::loadShaderUniforms(const QJsonValue & shaderUniVal)
{
   return loadShaderProperties(shaderUniVal, shaderUniforms);
}

bool MaterialDao::loadShaderAttributes(const QJsonValue & shaderAttrVal)
{
   return loadShaderProperties(shaderAttrVal, shaderAttributes);
}

bool MaterialDao::loadShaderProperties(const QJsonValue & shaderPropVal, QMap<QString, QString> & propContainer)
{
   if (!shaderPropVal.isObject())
      return false;
   QJsonObject shaderPropObj = shaderPropVal.toObject();

   for (QJsonObject::Iterator it = shaderPropObj.begin(); it != shaderPropObj.end(); ++it)
   {
      QString propName = it.key();
      QJsonValueRef propJsonVal = it.value();

      if (propJsonVal.isString())
         propContainer.insert(propName, propJsonVal.toString());
   }

   return true;
}

bool MaterialDao::loadEnvprobeType(const QJsonValue & envProbeVal)
{
   static QMap<QString, MaterialDao::EnvprobeType> envprobeTypeDict = {
      {"None",           EnvprobeType::None},
      {"EnvprobeObject", EnvprobeType::EnvprobeObject},
      {"TextureCubemap", EnvprobeType::TextureCubemap}
   };

   if (!envProbeVal.isString())
      return false;

   envprobeType = envprobeTypeDict.value(envProbeVal.toString(), EnvprobeType::None);
   return true;
}

bool MaterialDao::loadRenderPass(const QJsonValue & renderPassVal)
{
   static QMap<QString, RenderPass> renderPassDict = {
      {"Deferred", RenderPass::Deferred},
      {"Forward",  RenderPass::Forward}
   };

   if (!renderPassVal.isString())
      return false;

   renderPass = renderPassDict.value(renderPassVal.toString(), RenderPass::Deferred);
   return true;
}

bool MaterialDao::loadLightingModel(const QJsonValue & lightingMdlVal)
{
   if (!lightingMdlVal.isString())
      return false;

   lightingModel = lightingMdlVal.toString();
   return true;
}
}
