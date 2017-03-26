//
// Created by patryk on 13.08.16.
//

#ifndef ZINOT_PROJECT_SHADERDAO_HPP
#define ZINOT_PROJECT_SHADERDAO_HPP

#include <GL/gl.h>
#include <glm/glm.hpp>

#include <QString>
#include <QMap>
#include <QJsonObject>

#include <zinot-utils/json/JsonDao.hpp>
#include <cstring>

namespace Zinot
{

class ShaderDescDao : public JsonDao
{
public:
   enum class AttribType
   {
      None, Position, Normal, Tangent, UV, Color, Weight
   };

   enum class UniformDataType
   {
      None,
      Mat3, Mat4,
      Vec2, Vec3, Vec4,
      Bool, Int, Uint, Float, Double,
      Sampler1D, Sampler2D, Sampler3D, SamplerCube
   };

   union UniformDefaults
   {
      UniformDefaults()
      { std::memset(this, 0, sizeof(UniformDefaults)); }

      enum class NoneDefaults
      {
         None
      };
      enum class Mat3Defaults
      {
         Identity
      };
      enum class Mat4Defaults
      {
         Identity, Model, View, Projection
      };
      enum class Sampler1DDefaults
      {
         White
      };
      enum class Sampler2DDefaults
      {
         White, Black, FlatNormal
      };
      enum class Sampler3DDefaults
      {
         Fog
      };
      enum class SamplerCubeDefaults
      {
         Sky
      };

      NoneDefaults noneDefaults;
      Mat3Defaults mat3Defaults;
      Mat4Defaults mat4Defaults;

      glm::vec2 vec2Defaults;
      glm::vec3 vec3Defaults;
      glm::vec4 vec4Defaults;

      GLboolean boolVal;
      GLint intVal;
      GLuint uintVal;
      GLfloat floatVal;
      GLdouble doubleVal;

      Sampler1DDefaults sampler1DDefaults;
      Sampler2DDefaults sampler2DDefaults;
      Sampler3DDefaults sampler3DDefaults;
      SamplerCubeDefaults samplerCubeDefaults;
   };

   struct UniformType
   {
      UniformDataType dataType;
      UniformDefaults defVal;
   };
protected:
   QMap<QString, AttribType> shdAttributes;
   QMap<QString, UniformType> shdUniforms;
   QString vsPath, fsPath;

   bool loadShdAttributes(const QJsonValue & attribsVal);
   void loadShdAttribute(const QString & attrName, const QJsonValue & attrVal);

   bool loadShdUniforms(const QJsonValue & uniformsVal);
   void loadShdUniform(const QString & uniformName, const QJsonValue & uniformVal);

   ShaderDescDao::UniformDefaults getUniformDefault(const QString & defaultStr, UniformDataType dataType) const;
   ShaderDescDao::UniformDataType getUniformDataType(const QString & dataTypeStr) const;
public:
   virtual bool loadFromJsonDoc(const QJsonDocument & jsonDoc) override;

   const QMap<QString, AttribType> & getShdAttributes() const;
   const QMap<QString, UniformType> & getShdUniforms() const;
   const QString & getVsPath() const;
   const QString & getFsPath() const;
};
}

#endif //ZINOT_PROJECT_SHADERDAO_HPP
