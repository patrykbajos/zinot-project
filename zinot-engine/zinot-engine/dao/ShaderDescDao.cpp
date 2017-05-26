//
// Created by patryk on 13.08.16.
//
#include "../../../glloadgen/gl_core_3_3.hpp"
#include "ShaderDescDao.hpp"
#include <QFile>

namespace Zinot
{
namespace ShaderDescKeys
{
const QString ShaderAttributesKey = "shaderAttributes";
const QString ShaderUniformsKey = "shaderUniforms";
const QString VertexShaderPathKey = "vertexShaderPath";
const QString FragmentShaderPathKey = "fragmentShaderPath";
}

bool ShaderDescDao::loadShdAttributes(const QJsonValue & attribsVal)
{
   if (!attribsVal.isObject())
      return false;
   QJsonObject attribsObj = attribsVal.toObject();

   for (QJsonObject::Iterator it = attribsObj.begin(); it != attribsObj.end(); ++it)
   {
      QString attrName = it.key();
      QJsonValueRef attrVal = it.value();

      loadShdAttribute(attrName, attrVal);
   }

   return true;
}

void ShaderDescDao::loadShdAttribute(const QString & attrName, const QJsonValue & attrVal)
{
   static const QMap<QString, AttribType> attribsDict = {
      {"None",     AttribType::None},
      {"Position", AttribType::Position},
      {"Normal",   AttribType::Normal},
      {"Tangent",  AttribType::Tangent},
      {"UV",       AttribType::UV},
      {"Color",    AttribType::Color},
      {"Weight",   AttribType::Weight}
   };
   AttribType attribType = attribsDict.value(attrVal.toString(), AttribType::None);

   shdAttributes.insert(attrName, attribType);
}

bool ShaderDescDao::loadShdUniforms(const QJsonValue & uniformsVal)
{
   if (!uniformsVal.isObject())
      return false;
   QJsonObject uniformsObj = uniformsVal.toObject();

   for (QJsonObject::Iterator it = uniformsObj.begin(); it != uniformsObj.end(); ++it)
   {
      QString uniformName = it.key();
      QJsonValueRef uniformVal = it.value();

      loadShdUniform(uniformName, uniformVal);
   }

   return true;
}

void ShaderDescDao::loadShdUniform(const QString & uniformName, const QJsonValue & uniformVal)
{
   if (!uniformVal.isString())
      return;
   QString uniStr = uniformVal.toString();

   QStringList uniList = uniStr.split(";");
   if (uniList.size() != 2)
      return;

   QString dataTypeStr = uniList[0];
   QString defaultStr = uniList[1];

   UniformType uniformType;
   uniformType.dataType = getUniformDataType(dataTypeStr);
   uniformType.defVal = getUniformDefault(defaultStr, uniformType.dataType);

   shdUniforms.insert(uniformName, uniformType);
}

ShaderDescDao::UniformDataType ShaderDescDao::getUniformDataType(const QString & dataTypeStr) const
{
   static const QMap<QString, UniformDataType> dataTypeDict = {
      {"None",        UniformDataType::None},
      {"mat3",        UniformDataType::Mat3},
      {"mat4",        UniformDataType::Mat4},
      {"vec2",        UniformDataType::Vec2},
      {"vec3",        UniformDataType::Vec3},
      {"vec4",        UniformDataType::Vec4},
      {"bool",        UniformDataType::Bool},
      {"int",         UniformDataType::Int},
      {"uint",        UniformDataType::Uint},
      {"float",       UniformDataType::Float},
      {"double",      UniformDataType::Double},
      {"sampler1D",   UniformDataType::Sampler1D},
      {"sampler2D",   UniformDataType::Sampler2D},
      {"sampler3D",   UniformDataType::Sampler3D},
      {"samplerCube", UniformDataType::SamplerCube}
   };

   return dataTypeDict.value(dataTypeStr, UniformDataType::None);
}

ShaderDescDao::UniformDefaults ShaderDescDao::getUniformDefault(const QString & defaultStr,
                                                                UniformDataType dataType) const
{
   UniformDefaults def;

   switch (dataType)
   {
      case UniformDataType::None:
      {
         def.noneDefaults = UniformDefaults::NoneDefaults::None;
      }
         break;
      case UniformDataType::Mat3:
      {
         static const QMap<QString, UniformDefaults::Mat3Defaults> dictMat3 = {
            {"Identity", UniformDefaults::Mat3Defaults::Identity}
         };
         def.mat3Defaults = dictMat3.value(defaultStr, UniformDefaults::Mat3Defaults::Identity);
      }
         break;
      case UniformDataType::Mat4:
      {
         static const QMap<QString, UniformDefaults::Mat4Defaults> dictMat4 = {
            {"Identity",   UniformDefaults::Mat4Defaults::Identity},
            {"Model",      UniformDefaults::Mat4Defaults::Model},
            {"View",       UniformDefaults::Mat4Defaults::View},
            {"Projection", UniformDefaults::Mat4Defaults::Projection}
         };
         def.mat4Defaults = dictMat4.value(defaultStr, UniformDefaults::Mat4Defaults::Identity);
      }
         break;
      case UniformDataType::Vec2:
      {
         QStringList valListVec2 = defaultStr.split(",");
         if (valListVec2.size() != 2)
         {
            def.vec2Defaults = glm::vec2(0.0f, 0.0f);
            break;
         }

         def.vec2Defaults.x = valListVec2[0].toFloat();
         def.vec2Defaults.y = valListVec2[1].toFloat();
      }
         break;
      case UniformDataType::Vec3:
      {
         QStringList valListVec3 = defaultStr.split(",");
         if (valListVec3.size() != 3)
         {
            def.vec3Defaults = glm::vec3(0.0f, 0.0f, 0.0f);
            break;
         }

         def.vec3Defaults.x = valListVec3[0].toFloat();
         def.vec3Defaults.y = valListVec3[1].toFloat();
         def.vec3Defaults.z = valListVec3[2].toFloat();
      }
         break;
      case UniformDataType::Vec4:
      {
         QStringList valListVec4 = defaultStr.split(",");
         if (valListVec4.size() != 4)
         {
            def.vec4Defaults = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
            break;
         }

         def.vec4Defaults.x = valListVec4[0].toFloat();
         def.vec4Defaults.y = valListVec4[1].toFloat();
         def.vec4Defaults.z = valListVec4[2].toFloat();
         def.vec4Defaults.w = valListVec4[3].toFloat();
      }
         break;
      case UniformDataType::Bool:
         if (defaultStr == "true")
            def.boolVal = gl::TRUE_;
         else
            def.boolVal = gl::FALSE_;
         break;
      case UniformDataType::Int:
         def.intVal = defaultStr.toInt();
         break;
      case UniformDataType::Uint:
         def.uintVal = defaultStr.toUInt();
         break;
      case UniformDataType::Float:
         def.floatVal = defaultStr.toFloat();
         break;
      case UniformDataType::Double:
         def.doubleVal = defaultStr.toDouble();
         break;
      case UniformDataType::Sampler1D:
      {
         static const QMap<QString, UniformDefaults::Sampler1DDefaults> dictSampler1D = {
            {"White", UniformDefaults::Sampler1DDefaults::White},
         };
         def.sampler1DDefaults = dictSampler1D.value(defaultStr, UniformDefaults::Sampler1DDefaults::White);
      }
         break;
      case UniformDataType::Sampler2D:
      {
         static const QMap<QString, UniformDefaults::Sampler2DDefaults> dictSampler2D = {
            {"White",      UniformDefaults::Sampler2DDefaults::White},
            {"Black",      UniformDefaults::Sampler2DDefaults::Black},
            {"FlatNormal", UniformDefaults::Sampler2DDefaults::FlatNormal},
         };
         def.sampler2DDefaults = dictSampler2D.value(defaultStr, UniformDefaults::Sampler2DDefaults::White);
      }
         break;
      case UniformDataType::Sampler3D:
      {
         static const QMap<QString, UniformDefaults::Sampler3DDefaults> dictSampler3D = {
            {"Fog", UniformDefaults::Sampler3DDefaults::Fog},
         };
         def.sampler3DDefaults = dictSampler3D.value(defaultStr, UniformDefaults::Sampler3DDefaults::Fog);
      }
         break;
      case UniformDataType::SamplerCube:
      {
         static const QMap<QString, UniformDefaults::SamplerCubeDefaults> dictSamplerCube = {
            {"Sky", UniformDefaults::SamplerCubeDefaults::Sky},
         };
         def.samplerCubeDefaults = dictSamplerCube.value(defaultStr, UniformDefaults::SamplerCubeDefaults::Sky);
      }
         break;
   }

   return def;
}

bool ShaderDescDao::loadFromJsonDoc(const QJsonDocument & jsonDoc)
{
   if (!jsonDoc.isObject())
      return false;
   QJsonObject shdDescObj = jsonDoc.object();

   if (shdDescObj.contains(ShaderDescKeys::ShaderAttributesKey))
   {
      QJsonValue shdAttrVal = shdDescObj[ShaderDescKeys::ShaderAttributesKey];
      if (!loadShdAttributes(shdAttrVal))
         return false;
   } else
      shdAttributes.clear();

   if (shdDescObj.contains(ShaderDescKeys::ShaderUniformsKey))
   {
      QJsonValue shdUniVal = shdDescObj[ShaderDescKeys::ShaderUniformsKey];
      if (!loadShdUniforms(shdUniVal))
         return false;
   } else
      shdUniforms.clear();

   vsPath = shdDescObj[ShaderDescKeys::VertexShaderPathKey].toString();
   fsPath = shdDescObj[ShaderDescKeys::FragmentShaderPathKey].toString();

   return true;
}

const ShaderDescDao::AttributesMap & ShaderDescDao::getShdAttributes() const
{
   return shdAttributes;
}

const ShaderDescDao::UniformsMap & ShaderDescDao::getShdUniforms() const
{
   return shdUniforms;
}

const QString & ShaderDescDao::getVsPath() const
{
   return vsPath;
}

const QString & ShaderDescDao::getFsPath() const
{
   return fsPath;
}
}