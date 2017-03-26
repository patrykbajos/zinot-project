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
   QMap<ShaderDescDao::AttribType, GLint> attribs;

   GLuint loadShaderSrcFromFile(const QString & path, GLenum type);
public:
   Shader();
   virtual ~Shader() override;

   GLenum loadFromFile(const QString & shdDescPath);

   GLuint getProgram()
   { return program; };
};
}


#endif //ZINOT_GPUPROGRAM_HPP
