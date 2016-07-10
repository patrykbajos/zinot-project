//
// Created by patryk on 18.04.16.
//

#include "Mipmap.hpp"
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

   // Allocate and copy
   data.reset(new uint8_t[dataSize]);
   std::memcpy(data.get(), FreeImage_GetBits(fiBitmapScaled), dataSize);

   FreeImage_Unload(fiBitmapScaled);

   return true;
}

bool Mipmap::compress(int squishFlags)
{
   std::unique_ptr<uint8_t[]> tempBlock;
   auto squishRequiredStorage = squish::GetStorageRequirements(width, height, squishFlags);
   tempBlock.reset(new uint8_t[squishRequiredStorage]);

   squish::CompressImage(data.get(), width, height, tempBlock.get(), squishFlags);

   // Safe delete uncompressed data and replace with pointer to compressed data
   dataSize = (uint32_t) squishRequiredStorage;
   data = std::move(tempBlock);
}
}
}