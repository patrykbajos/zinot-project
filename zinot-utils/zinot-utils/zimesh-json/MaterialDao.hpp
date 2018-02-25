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

   typedef QMap<QString, QString> ShdPropContainer;
private:
   QString name;
   bool drawable;
   QString shaderPath;
   ShdPropContainer shaderUniforms;
   ShdPropContainer shaderAttributes;
   EnvprobeType envprobeType;
   RenderPass renderPass;
   QString lightingModel;

   bool loadShaderProperties(const QJsonValue & shaderPropVal, ShdPropContainer & propContainer);
   bool loadShaderUniforms(const QJsonValue & shaderUniVal);
   bool loadShaderAttributes(const QJsonValue & shaderAttrVal);
   bool loadEnvprobeType(const QJsonValue & envProbeVal);
   bool loadRenderPass(const QJsonValue & renderPassVal);
   bool loadLightingModel(const QJsonValue & lightingMdlVal);
public:
   bool loadFromJsonValue(const QString & matName, const QJsonValue & matVal);

   const QString & getName() const
   {
      return name;
   }

   bool isDrawable() const
   {
      return drawable;
   }

   const QString & getShaderPath() const
   {
      return shaderPath;
   }

   const QMap<QString, QString> & getShaderUniforms() const
   {
      return shaderUniforms;
   }

   const QMap<QString, QString> & getShaderAttributes() const
   {
      return shaderAttributes;
   }

   EnvprobeType getEnvprobeType() const
   {
      return envprobeType;
   }

   RenderPass getRenderPass() const
   {
      return renderPass;
   }

   const QString & getLightingModel() const
   {
      return lightingModel;
   }
};
}

#endif //ZINOT_PROJECT_MATERIAL_HPP
