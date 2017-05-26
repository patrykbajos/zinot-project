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
private:
   QString name;
   bool drawable;
   QString shaderPath;
   QMap<QString, QString> shaderUniforms;
   QMap<QString, QString> shaderAttributes;
   EnvprobeType envprobeType;
   RenderPass renderPass;
   QString lightingModel;

   bool loadShaderProperties(const QJsonValue & shaderPropVal, QMap<QString, QString> & map);
   bool loadShaderUniforms(const QJsonValue & shaderUniVal);
   bool loadShaderAttributes(const QJsonValue & shaderAttrVal);
   bool loadEnvprobeType(const QJsonValue & envProbeVal);
   bool loadRenderPass(const QJsonValue & renderPassVal);
   bool loadLightingModel(const QJsonValue & lightingMdlVal);
public:
   bool loadFromJsonValue(const QString & matName, const QJsonValue & matVal);
};

}

#endif //ZINOT_PROJECT_MATERIAL_HPP
