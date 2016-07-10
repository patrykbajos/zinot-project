//
// Created by patryk on 14.02.16.
//

#ifndef ZINOTPROJECT_TEXIMAGE_HPP
#define ZINOTPROJECT_TEXIMAGE_HPP

#include <GL/gl.h>
#include <zinot-utils/Endian.hpp>

#define TEX_TEXIMAGEHEADER_SIZE (4*16)

namespace Zinot
{
namespace Tex
{
#pragma pack(push, 1)

struct TexImageHeader
{
   // glTexImage()
   GLenum target;    // GL_TEXTURE_xD
   GLint level;    // Mipmap level
   GLsizei width;    // 1D 2D 3D
   GLsizei height;    // For 2D and 3D
   GLsizei depth;  // Only for 3D

   // glCompressedTexImage()
   GLuint imageSize;

   void toEndian(Endian::Type inEndian, Endian::Type outEndian);
};

#pragma pack(pop)
}
}


#endif //ZINOTPROJECT_TEXIMAGE_HPP
