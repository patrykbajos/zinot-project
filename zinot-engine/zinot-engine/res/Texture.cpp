#include <gl_core_3_3.hpp>
#include "Texture.hpp"

#include <zinot-utils/zitex/Reader.hpp>

#include <FreeImage.h>

namespace Zinot
{
bool Texture::loadFromFile()
{
   Tex::Reader reader;
   Tex::Reader::Data data;

   reader.readFromFile(getName().toStdString(), data);
   auto & header = data.header;

   gl::GenTextures(1, &id);
   gl::BindTexture(gl::TEXTURE_2D, id);

   for (uint32_t it = 0; it < data.header->texImagesNum; ++it)
   {
      auto & tiHeader = data.texImage[it].header;

      gl::CompressedTexImage2D(gl::TEXTURE_2D, tiHeader->level, (GLenum) header->internalFormat,
                               tiHeader->width, tiHeader->height, 0,
                               tiHeader->imageSize, data.texImage[it].data);
   }

   gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MAG_FILTER, gl::LINEAR);
   gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MIN_FILTER, gl::LINEAR_MIPMAP_LINEAR);

   return true;
}

Texture::~Texture()
{
   if (gl::IsTexture(id))
      gl::DeleteTextures(1, &id);
}
}
