//
// Created by patryk on 14.02.16.
//

#include "TexImageHeader.hpp"

namespace Zitex
{

void TexImageHeader::toEndian(Zinot::Endian::Type inEndian, Zinot::Endian::Type outEndian)
{
   Zinot::Endian endian;

   // If UNKNOWN it means "convert to local endianness!" :D
   if (outEndian == Zinot::Endian::LOCAL)
      outEndian = endian.getLocalEndian();

   // glTexImage()
   endian.toEndian(inEndian, sizeof(target), &target, outEndian);    // GL_TEXTURE_xD
   endian.toEndian(inEndian, sizeof(level), &level, outEndian);    // Mipmap level
   endian.toEndian(inEndian, sizeof(width), &width, outEndian);   // 1D 2D 3D
   endian.toEndian(inEndian, sizeof(height), &height, outEndian);    // For 2D and 3D textures
   endian.toEndian(inEndian, sizeof(depth), &depth, outEndian);    // Only for 3D textures

   // Length of pixel data
   endian.toEndian(inEndian, sizeof(imageSize), &imageSize, outEndian);
}

}