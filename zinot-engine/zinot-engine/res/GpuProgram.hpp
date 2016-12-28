//
// Created by patryk on 09.02.16.
//

#ifndef ZINOT_GPUPROGRAM_HPP
#define ZINOT_GPUPROGRAM_HPP

#include <GL/gl.h>
#include <zinot-engine/res-sys/Resource.hpp>

namespace Zinot
{
class GpuProgram : public Resource
{
protected:
   GLuint vs, fs, program;
   GLuint loadShaderFromFile(const QString & path, GLenum type);
public:
   GpuProgram();
   virtual ~GpuProgram() override;

   GLenum loadFromFiles(const QString & vsPath, const QString & fsPath);

   GLuint getProgram()
   { return program; };
};
}


#endif //ZINOT_GPUPROGRAM_HPP
