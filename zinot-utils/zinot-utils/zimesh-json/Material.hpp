//
// Created by patryk on 01.11.16.
//

#ifndef ZINOT_PROJECT_MATERIAL_HPP
#define ZINOT_PROJECT_MATERIAL_HPP

#include <QString>
#include <QVector>

namespace Zimesh
{

class Material
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
   float transparency;
   QString fsPath;
   QString vsPath;
   SurfaceType surfaceType;
   EnvmapSource envmapSource;
   QVector<QString> depTex;
};

}

#endif //ZINOT_PROJECT_MATERIAL_HPP
