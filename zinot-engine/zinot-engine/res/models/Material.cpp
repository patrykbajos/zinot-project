//
// Created by patryk on 27.05.16.
//

#include "Material.hpp"

#include <QFileInfo>
#include <zinot-engine/res-sys/MapResMgr.hpp>

namespace Zinot
{

Material::Material()
{

}

Material::~Material()
{

}

bool Material::loadFromZimeshJsonMaterialDao(const Zimesh::MaterialDao & materialDao, MapResMgr * gpuProgsMgr)
{
   drawable = materialDao.isDrawable();
   metalness = materialDao.getMetalness();
   roughness = materialDao.getRoughness();
   alpha = materialDao.getAlpha();
   surfaceType = materialDao.getSurfaceType();
   envmapSource = materialDao.getEnvmapSource();

   // TODO: Textures
   // TODO: Shader

   QString vsPath = materialDao.getVsPath();
   QString fsPath = materialDao.getFsPath();

   QFileInfo fileInfo;
   fileInfo.setFile(vsPath);
   QString vsName = fileInfo.baseName();
   fileInfo.setFile(fsPath);
   QString fsName = fileInfo.baseName();

   QString shaderName = "shader_" + vsName + "_" + fsName;

   NamesRegister & namReg = gpuProgsMgr->getNamesRegister();
   namReg.

   return true;
}
}