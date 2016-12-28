//
// Created by patryk on 27.05.16.
//

#ifndef ZINOTENGINEPROJECT_MATERIAL_HPP
#define ZINOTENGINEPROJECT_MATERIAL_HPP

#include <QMap>

#include <zinot-engine/res/Texture.hpp>
#include <zinot-engine/res/GpuProgram.hpp>
#include <zinot-utils/zimesh-json/MaterialDao.hpp>

namespace Zinot
{

class Material
{
protected:
   bool drawable;
   float metalness;
   float roughness;
   float alpha;
   Zimesh::MaterialDao::SurfaceType surfaceType;
   Zimesh::MaterialDao::EnvmapSource envmapSource;

   QMap<GLuint, Texture *> tex;
   GpuProgram * gpuProgram;
public:
   Material();
   ~Material();

   bool loadFromZimeshJsonMaterialDao(const Zimesh::MaterialDao & materialDao, MapResMgr * gpuProgsMgr);
};
}


#endif //ZINOTENGINEPROJECT_MATERIAL_HPP
