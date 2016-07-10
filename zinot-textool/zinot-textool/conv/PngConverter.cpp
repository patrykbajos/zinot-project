//
// Created by patryk on 13.03.16.
//

#include "PngConverter.hpp"

#include <iostream>
#include <cmath>

#include <FreeImage.h>
#include <squish/squish.h>
#include <zinot-textool/conv/Mipmap.hpp>
#include <zinot-utils/tex/Writer.hpp>

namespace Zinot
{
namespace Textool
{
bool PngConverter::convert(const QString & inFileName, const Configuration & configuration)
{    // TODO: Support for 1D, 3D and Cubemaps textures
   std::string inFileStdStr = inFileName.toStdString();

   FREE_IMAGE_FORMAT fiFormat = getFiFormat(inFileStdStr.c_str());

   if (!isReadableFiFormat(fiFormat))
   {
      std::cerr << "[ERROR] Not readable FI format: " << inFileName.toStdString() << std::endl;
      return false;
   }

   FIBITMAP * fiBitmap = loadFiBitmap(inFileStdStr, fiFormat);

   if (fiBitmap == nullptr)
   {
      std::cerr << "[ERROR] FreeImage haven't loaded image!\n";
      return false;
   }

   std::vector<Mipmap> mipmaps;

   auto squishFlags = generateSquishFlags(configuration);

   if (!generateMipMaps(fiBitmap, configuration, mipmaps))
   {
      std::cerr << "[ERROR] Can't generate mipmaps!\n";
      return false;
   }

   if (!compressImages(mipmaps, configuration))
   {
      std::cerr << "[ERROR] Can't compress images!\n";
      return false;
   }

   QString outFileName = generateOutName(inFileName, configuration);

   if (!writeToTex(mipmaps, configuration, outFileName))
   {
      std::cerr << "[ERROR] Can not write to .zitex file!\n";
      return false;
   }

   if (fiBitmap) FreeImage_Unload(fiBitmap);

   return true;
}

int PngConverter::generateSquishFlags(const Configuration & configuration) const
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

bool PngConverter::generateMipMaps(FIBITMAP * fiBitmap, const Configuration & configuration,
                                   std::vector<Mipmap> & mipmaps) const
{    // TODO: Textures with depth support
   uint32_t width = FreeImage_GetWidth(fiBitmap);
   uint32_t height = FreeImage_GetHeight(fiBitmap);

   // Mipmaps num without mipmap 0
   uint32_t mipmapsMaxLevel = std::max(std::log2(width), std::log2(height));

   for (uint32_t mipmapLevel = 0; mipmapLevel <= mipmapsMaxLevel; ++mipmapLevel)
   {
      Mipmap mipmap;
      mipmap.createFromFiBitmap(fiBitmap, width, height,
                                0, mipmapLevel, configuration.getMipmapFilter());

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

bool PngConverter::compressImages(std::vector<Mipmap> & mipmaps, const Configuration & configuration) const
{
   if (configuration.isCompressed())
   {
      for (auto & mipmap : mipmaps)
      {
         // TODO: Passing flags as a parameter to the compressImage()
         mipmap.compress(generateSquishFlags(configuration));
      }
   }

   return true;
}

QString PngConverter::generateOutName(const QString & inFileName, const Configuration & configuration) const
{
   // section(".", 0, -2) copyes from begin to 2nd section from end.
   // The first section from end is the extension

   return inFileName.section(".", 0, -2).append(".zitex");
}

bool PngConverter::writeToTex(const std::vector<Mipmap> & mipmaps, const Configuration & configuration,
                              const QString & outName) const
{
   Tex::Writer texWriter;
   Tex::Writer::Data data;

   // Complete data for file header
   data.outEndian = Endian::LE;
   auto & header = data.header;

   header.target = configuration.getGlBindTexture().getTarget();
   header.format = configuration.getGlTexImage().getFormat();
   header.type = configuration.getGlTexImage().getType();
   header.internalFormat = configuration.getGlTexImage().getInternalFormat();
   header.isLE = (uint32_t) true;
   header.texImagesNum = (uint32_t) mipmaps.size();
   header.squishFlags = generateSquishFlags(configuration);

   // Complete data for mipmaps and mipmaps' headers
   for (auto & mipmap : mipmaps)
   {
      data.texImageData.push_back(mipmap.getData());

      Tex::TexImageHeader texImageHeader;
      texImageHeader.width = mipmap.getWidth();
      texImageHeader.height = mipmap.getHeight();
      texImageHeader.depth = mipmap.getDepth();
      texImageHeader.level = mipmap.getLevel();
      texImageHeader.imageSize = mipmap.getDataSize();
      //TODO: Support others targets
      texImageHeader.target = GL_TEXTURE_2D;

      data.texImageHeader.push_back(texImageHeader);
   }

   texWriter.write(outName.toStdString(), data);

   return true;
}

FREE_IMAGE_FORMAT PngConverter::getFiFormat(const char * inFile) const
{
   // Check type by file header
   FREE_IMAGE_FORMAT fiFormat = FreeImage_GetFileType(inFile);

   if (fiFormat == FIF_UNKNOWN)
   {
      //Check type by file resId
      fiFormat = FreeImage_GetFIFFromFilename(inFile);

      if (fiFormat == FIF_UNKNOWN)
      {
         std::cerr << "[SKIPPING] Could not get file format: " << inFile << std::endl;
         return fiFormat;
      }
   }

   return fiFormat;
}

bool PngConverter::isReadableFiFormat(FREE_IMAGE_FORMAT fiFormat) const
{
   if (!FreeImage_FIFSupportsReading(fiFormat))
   {
      std::cerr << "[SKIPPING] FreeImage can not read this image type." << std::endl;
      return false;
   }

   return true;
}

FIBITMAP * PngConverter::loadFiBitmap(const std::string & inFile, FREE_IMAGE_FORMAT fiFormat) const
{
   FIBITMAP * fiBitmap = FreeImage_Load(fiFormat, inFile.c_str());

   // If loading failed
   if (!fiBitmap)
   {
      std::cerr << "[SKIPPING] FreeImage can not load image: " << inFile << std::endl;
      return nullptr;
   }

   makeValidBpp(fiBitmap);
   flipVertically(fiBitmap);
   // Now we have converted to 32bpp and loaded image

   return fiBitmap;
}

bool PngConverter::makeValidBpp(FIBITMAP *& fiBitmap) const
{
   auto bpp = FreeImage_GetBPP(fiBitmap);
   if (bpp != 32)
   {
      FIBITMAP * bitmapConverted = FreeImage_ConvertTo32Bits(fiBitmap);


      if (bitmapConverted == nullptr)
      {
         std::cerr << "[SKIPPING] FreeImage can not convert image to 32bpp" << std::endl;
         return false;
      }

      // Swap
      FreeImage_Unload(fiBitmap);
      fiBitmap = bitmapConverted;
   }

   return true;
}

bool PngConverter::flipVertically(FIBITMAP * fiBitmap) const
{
   return (bool) FreeImage_FlipVertical(fiBitmap);
}
}
}