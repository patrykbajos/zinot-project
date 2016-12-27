//
// Created by patryk on 13.03.16.
//

#include "PngConverter.hpp"

#include <squish/squish.h>
#include <iostream>
#include <cmath>

#include <zinot-utils/zitex/Writer.hpp>
#include <zinot-textool/convert/PngLoader.hpp>

namespace Zinot
{
namespace Textool
{
bool PngConverter::convert(const QString & inFilePath, const ConfigDao & config)
{
// TODO: Support for 1D, 3D and Cubemaps textures
   FIBITMAP * fiBitmap = PngLoader::loadPng(inFilePath);

   if (fiBitmap == nullptr)
   {
      std::cerr << "[ERROR] FreeImage haven't loaded image!\n";
      return false;
   }

   std::vector<Mipmap> mipmaps;
   if (!generateMipmaps(fiBitmap, config, mipmaps))
   {
      std::cerr << "[ERROR] Can't generate mipmaps!\n";
      return false;
   }

   if (!compressMipmaps(mipmaps, config))
   {
      std::cerr << "[ERROR] Can't compress images!\n";
      return false;
   }

   QString outFileName = generateOutName(inFilePath, config);
   if (!writeToTex(mipmaps, config, outFileName))
   {
      std::cerr << "[ERROR] Can not write to .zitex file!\n";
      return false;
   }

   FreeImage_Unload(fiBitmap);
   return true;
}

bool PngConverter::generateMipmaps(FIBITMAP * fiBitmap, const ConfigDao & config,
                                   std::vector<Mipmap> & mipmaps) const
{    // TODO: Textures with depth support
   uint32_t width = FreeImage_GetWidth(fiBitmap);
   uint32_t height = FreeImage_GetHeight(fiBitmap);
   uint32_t mipmapsMaxLevel = (uint32_t) std::max(std::log2(width), std::log2(height));

   for (uint32_t mipmapLevel = 0; mipmapLevel <= mipmapsMaxLevel; ++mipmapLevel)
   {
      Mipmap mipmap;
      mipmap.createFromFiBitmap(fiBitmap, width, height,
                                0, mipmapLevel, config.getMipmapFilter());
      // TODO: Mipmap depth for 3D texture

      if (mipmap.getData() == nullptr)
         return false;

      mipmaps.push_back(std::move(mipmap));

      width /= 2;
      height /= 2;

      // Prevent width or height smaller than 1
      // It would happen if width and height weren't equal
      if (width < 1) width = 1;
      if (height < 1) height = 1;
   }

   return true;
}

bool PngConverter::compressMipmaps(std::vector<Mipmap> & mipmaps, const ConfigDao & config) const
{
   if (config.isCompressed())
   {
      for (auto & mipmap : mipmaps)
         mipmap.compress(config);
   }

   return true;
}

QString PngConverter::generateOutName(const QString & inFilePath, const ConfigDao & config) const
{
   // section(".", 0, -2) copyes from begin to 2nd section from end.
   // The first section from end is the extension

   return inFilePath.section(".", 0, -2).append(".zitex");
}

bool PngConverter::writeToTex(const std::vector<Mipmap> & mipmaps, const ConfigDao & config,
                              const QString & outFilePath) const
{
   Zitex::Writer texWriter;
   Zitex::Writer::Data data;

   // Complete data for file header
   //data.outEndian = Endian::LE;
   auto & header = data.header;

   header.isLE = true;
   header.target = config.getGlBindTexture().getTarget();
   header.format = config.getGlTexImage().getFormat();
   header.type = config.getGlTexImage().getType();
   header.internalFormat = config.getGlTexImage().getInternalFormat();
   header.isLE = (uint32_t) true;
   header.texImagesNum = (uint32_t) mipmaps.size();
   header.squishFlags = Mipmap::generateSquishFlags(config);

   // Complete data for mipmaps and mipmaps' headers
   for (auto & mipmap : mipmaps)
   {
      Zitex::TexImageHeader texImageHeader;
      texImageHeader.width = mipmap.getWidth();
      texImageHeader.height = mipmap.getHeight();
      texImageHeader.depth = mipmap.getDepth();
      texImageHeader.level = mipmap.getLevel();
      texImageHeader.imageSize = mipmap.getDataSize();
      texImageHeader.target = GL_TEXTURE_2D;
      //TODO: Support others targets

      std::unique_ptr<uint8_t[]> tiData(new uint8_t[texImageHeader.imageSize]);
      std::memcpy(tiData.get(), mipmap.getData().get(), texImageHeader.imageSize);

      data.texImageData.push_back(std::move(tiData));
      data.texImageHeaders.push_back(texImageHeader);
   }

   texWriter.write(outFilePath.toStdString(), data);

   return true;
}
}
}