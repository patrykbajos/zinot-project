//
// Created by patryk on 01.11.16.
//

#ifndef ZINOT_PROJECT_MATERIAL_HPP
#define ZINOT_PROJECT_MATERIAL_HPP

#include <QString>
#include <QMap>
#include <QJsonObject>

namespace Zimesh
{

class MaterialDao
{
public:
   enum SurfaceType{
      Opaque,
      Transparent
   };

   enum EnvprobeType
   {
      None,
      EnvprobeObject,
      TextureCubemap
   };

   enum RenderPass
   {
      Deferred,
      Forward
   };
private:
   QString name;
   bool drawable;
   QString shaderPath;
   QMap<QString, QString> shaderProperties;
   EnvprobeType envprobeType;
   RenderPass renderPass;
   SurfaceType surfaceType;

   bool loadShaderProperties(const QJsonValue & shaderPropVal);
   bool loadEnvprobeType(const QJsonValue & envProbeVal);
   bool loadRenderPass(const QJsonValue & renderPassVal);
   bool loadSurfaceType(const QJsonValue & surfTypeVal);
public:
   bool loadFromJsonValue(const QString & matName, const QJsonValue & matVal);

   const QString & getName() const;
   bool isDrawable() const;
   const QString & getShaderPath() const;
   const QMap<QString, QString> & getShaderProperties() const;
   EnvprobeType getEnvprobeType() const;
   RenderPass getRenderPass() const;
   SurfaceType getSurfaceType() const;
};

}

#endif //ZINOT_PROJECT_MATERIAL_HPP
