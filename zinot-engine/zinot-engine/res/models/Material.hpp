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

class Model;
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
      GLboolean boolVal;
      GLint intVal;
      GLuint uintVal;
      GLfloat floatVal;
      GLdouble doubleVal;
      GLuint sampler1DVal;
      GLuint sampler2DVal;
      GLuint sampler3DVal;
      GLuint samplerCubeVal;
   };
private:
   Model * parentModel;

   bool drawable;
   MaterialDao::EnvprobeType envprobeType;
   uint8_t lightingModelId;
   MaterialDao::RenderPass renderPass;

   MapResMgr::ResPtr<Shader> shader;
   QMap<GLint, UniformData> shaderUniforms;
   QMap<GLint, QString> shaderAttributes;
public:
   Material(Model * parentModel) : parentModel(parentModel) {}
   ~Material();

   bool loadFromZimeshJsonMaterialDao(const Zimesh::MaterialDao & materialDao);
};
}


#endif //ZINOTENGINEPROJECT_MATERIAL_HPP
