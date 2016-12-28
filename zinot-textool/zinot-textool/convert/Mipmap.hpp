//
// Created by patryk on 18.04.16.
//

#ifndef ZINOTENGINEPROJECT_MIPMAP_HPP
#define ZINOTENGINEPROJECT_MIPMAP_HPP

#ifdef _WIN32
#include <windows.h>
#endif
#include <FreeImage.h>
#include <memory>
#include <cstring>

#include <zinot-textool/config/ConfigDao.hpp>

namespace Zinot
{
namespace Textool
{
class Mipmap
{
protected:
   std::unique_ptr<uint8_t[]> data;
   uint32_t width, height, depth, dataSize, level;
public:
   const std::unique_ptr<uint8_t[]> & getData() const
   { return data; }

   std::unique_ptr<uint8_t[]> & getData()
   { return data; }

   uint32_t getWidth() const
   { return width; }

   uint32_t getHeight() const
   { return height; }

   uint32_t getDataSize() const
   { return dataSize; }

   uint32_t getDepth() const
   { return depth; }

   uint32_t getLevel() const
   { return level; }

   bool createFromFiBitmap(FIBITMAP * fiBitmap, uint32_t destWidth, uint32_t destHeight,
                           uint32_t destDepth, uint32_t destLevel, FREE_IMAGE_FILTER filter);
   bool compress(const ConfigDao & configuration);
   static int generateSquishFlags(const ConfigDao & configuration);
};
}
}

#endif //ZINOTENGINEPROJECT_MIPMAP_HPP
