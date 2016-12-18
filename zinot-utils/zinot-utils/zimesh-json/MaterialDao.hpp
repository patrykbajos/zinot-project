//
// Created by patryk on 01.11.16.
//

#ifndef ZINOT_PROJECT_MATERIAL_HPP
#define ZINOT_PROJECT_MATERIAL_HPP

#include <QString>
#include <QVector>
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

   enum EnvmapSource{
      None,
      StaticObject,
      StaticMesh,
      DynamicObject,
      DynamicMesh,
      Texture
   };
private:
   bool drawable;
   float metalness;
   float roughness;
   float alpha;
   QString fsPath;
   QString vsPath;
   SurfaceType surfaceType;
   EnvmapSource envmapSource;
   QVector<QString> depTex;

   void loadSurfaceType(const QJsonObject & matObj);
   void loadEnvmapSource(const QJsonObject & matObj);
   bool loadDepTex(const QJsonObject & matObj);
public:
   bool loadFromJsonValue(const QJsonValue & jsonVal);

   bool isDrawable() const
   {
      return drawable;
   }

   float getMetalness() const
   {
      return metalness;
   }

   float getRoughness() const
   {
      return roughness;
   }

   float getAlpha() const
   {
      return alpha;
   }

   const QString & getFsPath() const
   {
      return fsPath;
   }

   const QString & getVsPath() const
   {
      return vsPath;
   }

   SurfaceType getSurfaceType() const
   {
      return surfaceType;
   }

   EnvmapSource getEnvmapSource() const
   {
      return envmapSource;
   }

   const QVector<QString> & getDepTex() const
   {
      return depTex;
   }
};

}

#endif //ZINOT_PROJECT_MATERIAL_HPP
