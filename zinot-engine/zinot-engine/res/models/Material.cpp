//
// Created by patryk on 27.05.16.
//

#include "Material.hpp"

#include <assimp/cimport.h>

namespace Zinot
{

Material::Material()
{
   texDiff = nullptr;

   diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
   ambient = glm::vec3(0.8f, 0.8f, 0.8f);
   specular = 0.5f;
}

Material::~Material()
{
   if (texDiff)
      delete texDiff;
   /*if (texSpec)
      delete texSpec;
   if (texNorm)
      delete texNorm;*/
}

bool Material::processAiMaterial(QString modelDir, aiMaterial * aiMat, MapResMgr * texResMgr)
{
   aiString aiName;
   if (aiMat->Get(AI_MATKEY_NAME, aiName) != aiReturn_SUCCESS)
      return false;

   // Get path and change extension to .zitex
   if (QString(aiName.C_Str()) == AI_DEFAULT_MATERIAL_NAME)
      return true;

   if (!processParameters(aiMat))
      return false;

   if (!processTexDiff(modelDir, aiMat, texResMgr))
      return false;

   return true;
}

bool Material::processParameters(aiMaterial * aiMat)
{
   // Get parameters
   if (aiMat->Get(AI_MATKEY_SHININESS, specular) != aiReturn_SUCCESS)
      return false;

   aiColor3D aiAmbient;
   if (aiMat->Get(AI_MATKEY_COLOR_AMBIENT, aiAmbient) != aiReturn_SUCCESS)
      return false;
   ambient = glm::vec3(aiAmbient.r, aiAmbient.g, aiAmbient.b);

   aiColor3D aiDiff;
   if (aiMat->Get(AI_MATKEY_COLOR_DIFFUSE, aiDiff) != aiReturn_SUCCESS)
      return false;
   diffuse = glm::vec3(aiDiff.r, aiDiff.g, aiDiff.b);

   return true;
}

bool Material::processTexDiff(QString modelDir, aiMaterial * aiMat, MapResMgr * texResMgr)
{
   // Load and check path
   aiString aiPath;
   aiMat->Get(AI_MATKEY_TEXTURE_DIFFUSE(0), aiPath);
   QString texturePath = QString(aiPath.C_Str());
   if (texturePath.isEmpty())
   {
      texDiff = nullptr;
      return true;
   }

   // Get relative to engine path
   QString pathWithZitexExt(texturePath.section(".", 0, -2).append(".zitex"));
   QString fullPath = modelDir + "/" + pathWithZitexExt;

   // Create texture resource
   auto resId = texResMgr->getNamesRegister().addName(fullPath);
   texDiff = (Texture *) texResMgr->getRes(resId);
   if (!texDiff)
      texDiff = (Texture *) texResMgr->newRes(resId, new Texture(), true);

   // Try loat dexture
   if (!texDiff->loadFromFile())
   {
      texResMgr->deleteRes(resId);
      texDiff = nullptr;
      return false;
   }

   return true;
}
}