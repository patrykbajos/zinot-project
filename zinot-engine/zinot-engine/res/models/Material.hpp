//
// Created by patryk on 27.05.16.
//

#ifndef ZINOTENGINEPROJECT_MATERIAL_HPP
#define ZINOTENGINEPROJECT_MATERIAL_HPP

#include <zinot-utils/zimesh-json/MaterialDao.hpp>
#include <zinot-engine/res-sys/MapResMgr.hpp>
#include <zinot-engine/res/Shader.hpp>
#include <zinot-engine/res/Texture.hpp>

namespace Zinot
{

using Zimesh::MaterialDao;
using ShaderDescDao;

class Material
{
public:
   union UniformData {
      glm::mat3 mat3Val;
      glm::mat4 mat4Val;
      glm::vec2 vec2Val;
      glm::vec3 vec3Val;
      glm::vec4 vec4Val;
      bool boolVal;
      int32_t intVal;
      uint32_t uintVal;
      float floatVal;
      double doubleVal;
      GLuint sampler1DVal;
      GLuint sampler2DVal;
      GLuint sampler3DVal;
      GLuint samplerCubeVal;
   };
private:
   bool drawable;
   MaterialDao::EnvprobeType envprobeType;
   uint8_t lightingModelId;
   MaterialDao::RenderPass renderPass;

   MapResMgr::ResPtr<Shader> shader;
   QMap<GLint, UniformData> shaderUniforms;
   QMap<GLint, QString> shaderAttributes;
public:
   Material();
   ~Material();

   bool loadFromZimeshJsonMaterialDao(const Zimesh::MaterialDao & materialDao);
};
}


#endif //ZINOTENGINEPROJECT_MATERIAL_HPP
