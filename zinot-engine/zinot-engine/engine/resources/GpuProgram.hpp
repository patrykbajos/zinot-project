//
// Created by patryk on 09.02.16.
//

#ifndef ZINOT_GPUPROGRAM_HPP
#define ZINOT_GPUPROGRAM_HPP

#include <GL/gl.h>
#include <zinot-engine/resources/Resource.hpp>

namespace Zinot
{
class GpuProgram : public Resource
{
protected:
   GLuint program;
public:
   GpuProgram();
   virtual ~GpuProgram() override;

   GLenum loadFromShaders(GLuint vertexShader, GLuint fragmentShader);

   GLuint getProgram()
   { return program; };
};
}


#endif //ZINOT_GPUPROGRAM_HPP
