#ifndef ZINOTPROJECT_HEADER_HPP
#define ZINOTPROJECT_HEADER_HPP

#include <GL/gl.h>
#include <zinot-utils/Endian.hpp>

namespace Zitex
{

#define ZITEX_FILEHEADER_SIZE 128
#pragma pack(push, 1)
struct FileHeader
{
   // Basic informations
   uint32_t isLE;    // true = LE, false = BE
   uint32_t version; // Version of format

   // glBindTexture()
   GLenum target;    // GL_TEXTURE_2D etc.

   // glTexParameter()
   GLenum LOD_BIAS;   // Lod bias
   GLenum MIN_FILTER;  // Minification (-) filter
   GLenum MAG_FILTER;  // Magnification (+) filter
   GLenum MIN_LOD;     // Minimal LOD
   GLenum MAX_LOD;     // Maximum LOD
   GLenum MAX_LEVEL;   // Maximim mipmap level
   GLenum WRAP_S;      // Texture wrapping S,T,R
   GLenum WRAP_T;
   GLenum WRAP_R;

   // glCompressedTexImage() and glTexImage()
   GLint internalFormat;
   // only for glTexImage()
   GLenum format;
   GLenum type;

   // Number of texture images
   uint32_t texImagesNum;

   // libSquish compression flags
   int squishFlags;

   void toEndian(Zinot::Endian::Type outEndian);
   Zinot::Endian::Type getEndian();
};
#pragma pack(pop)

}

#endif //ZINOTPROJECT_HEADER_HPP