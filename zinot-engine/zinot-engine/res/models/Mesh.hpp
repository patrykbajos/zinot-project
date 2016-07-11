//
// Created by patryk on 27.05.16.
//

#ifndef ZINOTENGINEPROJECT_MESH_HPP
#define ZINOTENGINEPROJECT_MESH_HPP

#include <GL/gl.h>

namespace Zinot
{
struct Mesh
{
   GLenum type;

   GLuint baseVertex;
   GLuint indices;
   GLuint count;

   uint32_t matIt;
};
}

#endif //ZINOTENGINEPROJECT_MESH_HPP
