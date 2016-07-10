//
// Created by patryk on 09.02.16.
//

#include <gl_core_3_3.hpp>

#include "GpuProgram.hpp"

namespace Zinot
{

GpuProgram::GpuProgram()
{
   program = 0;
}

GpuProgram::~GpuProgram()
{
   if (program)
      gl::DeleteProgram(program);
}

GLenum GpuProgram::loadFromShaders(GLuint vertexShader, GLuint fragmentShader)
{
   program = gl::CreateProgram();

   gl::AttachShader(program, vertexShader);
   gl::AttachShader(program, fragmentShader);
   gl::LinkProgram(program);

   return gl::GetError();
}
}
