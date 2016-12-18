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
static const QString metalnessKey = "metalness";
static const QString roughnessKey = "roughness";
static const QString alphaKey = "alpha";
static const QString fsKey = "fragmentShader";
static const QString vsKey = "vertexShader";
static const QString depTexKey = "dependentTextures";
static const QString envmapSourceKey = "envmapSource";
static const QString surfaceTypeKey = "surfaceType";
//static const QString Key = "";

}

bool MaterialDao::loadFromJsonValue(const QJsonValue & jsonVal)
{
   if (!jsonVal.isObject())
      return false;

   QJsonObject matObj = jsonVal.toObject();

   drawable = matObj[MaterialKeys::drawableKey].toBool(true);
   metalness = (float) matObj[MaterialKeys::metalnessKey].toDouble(0.0);
   roughness = (float) matObj[MaterialKeys::roughnessKey].toDouble(0.5);
   alpha = (float) matObj[MaterialKeys::alphaKey].toDouble(0.0);
   fsPath = matObj[MaterialKeys::fsKey].toString();
   vsPath = matObj[MaterialKeys::vsKey].toString();

   loadSurfaceType(matObj);
   loadEnvmapSource(matObj);

   return loadDepTex(matObj);
}

void MaterialDao::loadSurfaceType(const QJsonObject & matObj)
{
   static QMap<QString, SurfaceType> surfaceTypeDict = {
      {"opaque",      SurfaceType::Opaque},
      {"transparent", SurfaceType::Transparent}
   };
   QJsonValue surfTypeVal = matObj[MaterialKeys::surfaceTypeKey];
   QString surfTypeName = surfTypeVal.toString();

   surfaceType = surfaceTypeDict.value(surfTypeName, SurfaceType::Opaque);
}

void MaterialDao::loadEnvmapSource(const QJsonObject & matObj)
{
   static QMap<QString, EnvmapSource> envmapSourceDict = {
      {"none",          EnvmapSource::None},
      {"staticObject",  EnvmapSource::StaticObject},
      {"staticMesh",    EnvmapSource::StaticMesh},
      {"dynamicObject", EnvmapSource::DynamicObject},
      {"dynamicMesh",   EnvmapSource::DynamicMesh},
      {"texture",       EnvmapSource::Texture}
   };

   QJsonValue envSrcVal = matObj[MaterialKeys::envmapSourceKey];
   QString envSrcName = envSrcVal.toString();
   envmapSource = envmapSourceDict.value(envSrcName, EnvmapSource::StaticObject);
}

bool MaterialDao::loadDepTex(const QJsonObject & matObj)
{
   QJsonValue depTexVal = matObj[MaterialKeys::depTexKey];
   if (!depTexVal.isArray())
      return false;

   for (QJsonValue val : depTexVal.toArray())
   {
      if (val.isString())
         depTex.push_back(val.toString());
   }

   return true;
}
}
