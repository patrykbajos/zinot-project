//
// Created by patryk on 23.04.17.
//

#ifndef ZINOT_PROJECT_VERTEXATTRIBPOINTER_HPP
#define ZINOT_PROJECT_VERTEXATTRIBPOINTER_HPP

#include <GL/gl.h>

namespace Zinot
{

class VertexAttribPointer
{
private:
   GLuint index;
   GLint size;
   GLenum type;
   GLboolean normalized;
   GLsizei stride;
   GLvoid * pointer;

};

}

#endif //ZINOT_PROJECT_VERTEXATTRIBPOINTER_HPP
