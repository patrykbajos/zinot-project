//
// Created by patryk on 13.08.16.
//

#ifndef ZINOT_PROJECT_SHADERDAO_HPP
#define ZINOT_PROJECT_SHADERDAO_HPP

#include <QString>
#include <QMap>
#include <QJsonObject>
#include <gl_core_3_3.hpp>

namespace Zinot
{

class ShaderDescDao
{
public:
   enum AttribType
   {
      Position, Normal, Tangent, UV, Color, Weight
   };

   enum UniformDataType
   {
      Mat3, Mat4,
      Vec2, Vec3, Vec4,
      Bool, Int, Uint, Float, Double,
      Sampler1D, Sampler2D, Sampler3D, SamplerCube
   };
   union UniformDefaults
   {
      enum Mat3Defaults
      {
         Identity
      };
      enum Mat4Defaults
      {
         Model, View, Projection, Identity
      };
      enum Sampler2DDefaults
      {
         White, Black, FlatNormal
      };

      Mat3Defaults mat3Defaults;
      Mat4Defaults mat4Defaults;
      Sampler2DDefaults sampler2DDefaults;
      GLboolean boolVal;
      GLint intVal;
      GLuint uintVal;
      GLfloat floatVal;
      GLdouble doubleVal;
   };
   struct UniformType
   {
      UniformDataType dataType;
      UniformDefaults defaults;
   };
protected:
   QMap<QString, AttribType> shdAttributes;
   QMap<QString, UniformType> shdUnifroms;
   QString vsPath, fsPath;

   bool loadShdAttributes(const QJsonValue & attribsVal);
   void loadShdAttribute(const QString & attrName, const QJsonValue & attrVal);

   bool loadShdUniforms(const QJsonValue & uniformsVal);
   void loadShdUniform(const QString & uniformName, const QJsonValue & uniformVal);
public:
   bool loadFromJsonVal(const QJsonValue & shdDescVal);
};
}

#endif //ZINOT_PROJECT_SHADERDAO_HPP
