//
// Created by patryk on 09.02.16.
//

#ifndef ZINOT_GPUPROGRAM_HPP
#define ZINOT_GPUPROGRAM_HPP

#include <gl_core_3_3.hpp>
#include <zinot-engine/res-sys/Resource.hpp>

namespace Zinot
{

class Shader : public Resource
{
protected:
   GLuint program;
   GLuint loadShaderFromFile(const QString & path, GLenum type);
public:
   Shader();
   virtual ~Shader() override;

   GLenum loadFromFile(const QString & shaderPath);

   GLuint getProgram()
   { return program; };
};
}


#endif //ZINOT_GPUPROGRAM_HPP
