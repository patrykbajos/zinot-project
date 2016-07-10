//
// Created by patryk on 05.02.16.
//

#ifndef ZINOT_SHADER_HPP
#define ZINOT_SHADER_HPP

#include <GL/gl.h>
#include <zinot-engine/resources/Resource.hpp>

namespace Zinot
{
class Shader : public Resource
{
protected:
   GLuint shader;
public:
   GLenum loadFromFile(GLuint type);

   GLuint getShader()
   { return shader; };
};
}

#endif //ZINOT_SHADER_HPP
