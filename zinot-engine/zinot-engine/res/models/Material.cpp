//
// Created by patryk on 27.05.16.
//

#include "Material.hpp"

#include <zinot-engine/eng/Engine.hpp>
#include <zinot-engine/res/models/Model.hpp>
#include <zinot-engine/eng/ResMgrList.hpp>
#include <zinot-utils/Logger.hpp>

namespace Zinot
{

Material::~Material()
{

}

bool Material::loadFromZimeshJsonMaterialDao(const Zimesh::MaterialDao & materialDao)
{
   /*
   bool drawable;
   MaterialDao::EnvprobeType envprobeType;
   uint8_t lightingModelId;
   MaterialDao::RenderPass renderPass;

   MapResMgr::ResPtr<Shader> shader;
   QMap<GLint, UniformData> shaderUniforms;
   QMap<GLint, QString> shaderAttributes;
   */
   auto & lml = parentModel->getEngine()->getScenePtr()->getLightingModelList();
   MapResMgr * shdMgr = getResMgrOfType(ResMgrType::ShadersMgr);

   drawable = materialDao.isDrawable();
   envprobeType = materialDao.getEnvprobeType();
   lightingModelId = static_cast<uint8_t>(lml.indexOf(materialDao.getLightingModel()));
   renderPass = materialDao.getRenderPass();

   shader = shdMgr->getRes<Shader>(materialDao.getShaderPath());
   if(!shader->isLoaded())
   {
      GLenum err = shader->loadFromFile(materialDao.getShaderPath());

      if(err)
      {
         auto & logger = Logger::getInstance();
         logger.log("[ERROR]: Error loading shader \"" + materialDao.getShaderPath()
                    + "\" in shader \"" + materialDao.getName() + "\".");
      }
   }

   auto & mtUni = materialDao.getShaderUniforms();
   auto & shdUni = shader->getUniforms();
   auto & shdUniTypes = shader->getUniformTypes();

   for (MaterialDao::ShdPropContainer::ConstIterator it = mtUni.constBegin(); it != mtUni.constEnd(); ++it)
   {
      auto & uniName = it.key();
      auto & uniValStr = it.value();

      auto shdUniId = shdUni[uniName];
      auto & shdUniType = shdUniTypes[shdUniId];

      switch(shdUniType.dataType)
      {
         case ShaderDescDao::UniformDataType::None:
         {
            break;
         }
         case ShaderDescDao::UniformDataType::Mat3:
         {
            UniformData data;
            QVector<QStringRef> floatsStr = uniValStr.splitRef(",");


            break;
         }
         case ShaderDescDao::UniformDataType::Mat4:
         {
            break;
         }
         case ShaderDescDao::UniformDataType::Vec2:
         {
            break;
         }
         case ShaderDescDao::UniformDataType::Vec3:
         {
            break;
         }
         case ShaderDescDao::UniformDataType::Vec4:
         {
            break;
         }
         case ShaderDescDao::UniformDataType::Bool:
         {
            break;
         }
         case ShaderDescDao::UniformDataType::Int:
         {
            break;
         }
         case ShaderDescDao::UniformDataType::Uint:
         {
            break;
         }
         case ShaderDescDao::UniformDataType::Float:
         {
            break;
         }
         case ShaderDescDao::UniformDataType::Double:
         {
            break;
         }
         case ShaderDescDao::UniformDataType::Sampler1D:
         {
            break;
         }
         case ShaderDescDao::UniformDataType::Sampler2D:
         {
            break;
         }
         case ShaderDescDao::UniformDataType::Sampler3D:
         {
            break;
         }
         case ShaderDescDao::UniformDataType::SamplerCube:
         {
            break;
         }
      }
   }

   auto & mtAttr = materialDao.getShaderAttributes();
   auto & shdAttr = shader->getAttribs();
   auto & shdAttrTypes = shader->getAttribTypes();

   for (MaterialDao::ShdPropContainer::ConstIterator it = mtAttr.constBegin(); it != mtAttr.constEnd(); ++it)
   {

   }

   return true;
}

}