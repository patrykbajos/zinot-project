//
// Created by patryk on 01.11.16.
//

#include "MaterialDao.hpp"

#include <QMap>
#include <QJsonArray>

namespace Zimesh
{
namespace MaterialKeys
{

static const QString drawableKey = "drawable";
static const QString shaderPathKey = "shaderPath";
static const QString shaderPropertiesKey = "shaderProperties";
static const QString envprobeTypeKey = "envprobeType";
static const QString renderPassKey = "renderPass";
static const QString surfaceTypeKey = "surfaceType";

}

bool MaterialDao::loadFromJsonValue(const QString & matName, const QJsonValue & matVal)
{
   if (!matVal.isObject())
      return false;
   QJsonObject matObj = matVal.toObject();

   name = matName;
   drawable = matObj[MaterialKeys::drawableKey].toBool(true);
   shaderPath = matObj[MaterialKeys::shaderPathKey].toString();

   if (matObj.contains(MaterialKeys::shaderPropertiesKey))
   {
      QJsonValue shaderPropVal = matObj[MaterialKeys::shaderPropertiesKey];
      if (!loadShaderProperties(shaderPropVal))
         return false;
   } else
   {
      shaderProperties.clear();
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

   if (matObj.contains(MaterialKeys::surfaceTypeKey))
   {
      QJsonValue surfTypeVal = matObj[MaterialKeys::surfaceTypeKey];
      if (!loadSurfaceType(surfTypeVal))
         return false;
   } else
   {
      surfaceType = SurfaceType::Opaque;
   }

   return true;
}

bool MaterialDao::loadShaderProperties(const QJsonValue & shaderPropVal)
{
   if (!shaderPropVal.isObject())
      return false;
   QJsonObject shaderPropObj = shaderPropVal.toObject();

   for (QJsonObject::Iterator it = shaderPropObj.begin(); it != shaderPropObj.end(); ++it)
   {
      QString propName = it.key();
      QJsonValueRef propJsonVal = it.value();

      if (!propJsonVal.isString())
         continue;

      shaderProperties.insert(propName, propJsonVal.toString());
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

bool MaterialDao::loadSurfaceType(const QJsonValue & surfTypeVal)
{
   static QMap<QString, SurfaceType> surfaceTypeDict = {
      {"Opaque",      SurfaceType::Opaque},
      {"Transparent", SurfaceType::Transparent}
   };

   if (!surfTypeVal.isString())
      return false;

   surfaceType = surfaceTypeDict.value(surfTypeVal.toString(), SurfaceType::Opaque);
   return true;
}

const QString & MaterialDao::getName() const
{
   return name;
}

bool MaterialDao::isDrawable() const
{
   return drawable;
}

const QString & MaterialDao::getShaderPath() const
{
   return shaderPath;
}

const QMap<QString, QString> & MaterialDao::getShaderProperties() const
{
   return shaderProperties;
}

MaterialDao::EnvprobeType MaterialDao::getEnvprobeType() const
{
   return envprobeType;
}

MaterialDao::RenderPass MaterialDao::getRenderPass() const
{
   return renderPass;
}

MaterialDao::SurfaceType MaterialDao::getSurfaceType() const
{
   return surfaceType;
}
}
