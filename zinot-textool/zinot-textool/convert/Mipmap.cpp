//
// Created by patryk on 18.04.16.
//

#include "Mipmap.hpp"

#include <memory>
#include <squish/squish.h>

namespace Zinot
{
namespace Textool
{
bool Mipmap::createFromFiBitmap(FIBITMAP * fiBitmap, uint32_t destWidth, uint32_t destHeight,
                                uint32_t destDepth, uint32_t destLevel, FREE_IMAGE_FILTER filter)
{
   FIBITMAP * fiBitmapScaled = FreeImage_Rescale(fiBitmap, destWidth, destHeight, filter);

   if (!fiBitmapScaled)
      return false;

   width = destWidth;
   height = destHeight;
   depth = destDepth;
   level = destLevel;

   // BPP is "bits per pixel"
   // For bytes per pixel = BPP / 8
   // Whole data size is bytes_per_pixel * width * height
   dataSize = (FreeImage_GetBPP(fiBitmapScaled) / 8) * width * height;
   data.reset(new uint8_t[dataSize]);

   // Copy scan lines from bottom to top as OpenGL wants
   for (uint32_t y = 0; y < height; ++y)
   {
      static uint32_t dataLineSize = width * 4;
      void * fiScanLine = FreeImage_GetScanLine(fiBitmap, y);
      void * dataScanLine = data.get() + (dataLineSize * y);

      std::memcpy(dataScanLine, fiScanLine, dataLineSize);

      // Convert BGRA to RGBA
      uint32_t * dataScanLinePixels = (uint32_t *) dataScanLine;
      for (uint32_t x = 0; x < width; ++x)
      {
         uint8_t * pixelComponents = (uint8_t *) &dataScanLinePixels[x];
         // BGRA -> RGBA
         std::swap(pixelComponents[0], pixelComponents[2]);
      }
   }

   FreeImage_Unload(fiBitmapScaled);
   return true;
}

int Mipmap::generateSquishFlags(const ConfigDao & configuration)
{
   switch (configuration.getGlTexImage().getInternalFormat())
   {
      // The same result for RGBA and RGB
      case GL_COMPRESSED_RGB_S3TC_DXT1_EXT:
      case GL_COMPRESSED_RGBA_S3TC_DXT1_EXT:
         return squish::kDxt1;
         break;
      case GL_COMPRESSED_RGBA_S3TC_DXT3_EXT:
         return squish::kDxt3;
         break;
      case GL_COMPRESSED_RGBA_S3TC_DXT5_EXT:
         return squish::kDxt5;
         break;
      default:
         return squish::kDxt1;
         break;
   }
}

bool Mipmap::compress(const ConfigDao & configuration)
{
   int squishFlags = generateSquishFlags(configuration);
   auto squishRequiredStorage = squish::GetStorageRequirements(width, height, squishFlags);

   std::unique_ptr<uint8_t[]> tempBlock(new uint8_t[squishRequiredStorage]);
   squish::CompressImage(data.get(), width, height, tempBlock.get(), squishFlags);

   // Safe delete uncompressed data and replace with pointer to compressed data
   dataSize = (uint32_t) squishRequiredStorage;
   data = std::move(tempBlock);
}
}
}