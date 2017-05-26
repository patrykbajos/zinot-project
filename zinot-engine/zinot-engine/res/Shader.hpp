//
// Created by patryk on 09.02.16.
//

#ifndef ZINOT_GPUPROGRAM_HPP
#define ZINOT_GPUPROGRAM_HPP

#include <GL/gl.h>
#include <zinot-engine/res-sys/Resource.hpp>
#include <zinot-engine/dao/ShaderDescDao.hpp>

namespace Zinot
{

class Shader : public Resource
{
protected:
   GLuint program;
   QMap<QString, GLint> uniforms;
   QMap<GLint, ShaderDescDao::UniformType> uniformTypes;

   QMap<QString, GLint> attribs;
   QMap<GLint, ShaderDescDao::AttribType> attribTypes;

   GLuint loadShaderSrcFromFile(const QString & path, GLenum type);
   void getUniforms(const ShaderDescDao & shdDescDao);
   void getAttribs(const ShaderDescDao & shdDescDao);
public:
   Shader();
   virtual ~Shader() override;
   GLenum loadFromFile(const QString & shdDescPath);

   GLuint getProgram()
   {
      return program;
   };

   const QMap<QString, GLint> & getUniforms() const
   {
      return uniforms;
   }

   const QMap<GLint, ShaderDescDao::UniformType> & getUniformTypes() const
   {
      return uniformTypes;
   }

   const QMap<QString, GLint> & getAttribs() const
   {
      return attribs;
   }

   const QMap<GLint, ShaderDescDao::AttribType> & getAttribTypes() const
   {
      return attribTypes;
   }
};
}


#endif //ZINOT_GPUPROGRAM_HPP
