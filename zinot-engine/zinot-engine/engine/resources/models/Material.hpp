//
// Created by patryk on 27.05.16.
//

#ifndef ZINOTENGINEPROJECT_MATERIAL_HPP
#define ZINOTENGINEPROJECT_MATERIAL_HPP

#include <glm/glm.hpp>
#include <assimp/scene.h>

#include <zinot-engine/engine/resources/Texture.hpp>

namespace Zinot
{
class Material
{
protected:
public:
   Texture * getTexDiff() const
   {
      return texDiff;
   }

protected:
   Texture * texDiff;
   //Texture * texSpec;
   //Texture * texNorm;

   glm::vec3 diffuse;
   glm::vec3 ambient;
   float specular;

   bool processParameters(aiMaterial * aiMat);
   bool processTexDiff(QString modelDir, aiMaterial * aiMat, MapResMgr * texResMgr);
   //bool processTexSpec(QString modelDir, aiMaterial * aiMat, MapResMgr * texResMgr);
   //bool processTexNorm(QString modelDir, aiMaterial * aiMat, MapResMgr * texResMgr);
public:
   Material();
   ~Material();
   bool processAiMaterial(QString modelDir, aiMaterial * aiMat, MapResMgr * texResMgr);
};
}


#endif //ZINOTENGINEPROJECT_MATERIAL_HPP
