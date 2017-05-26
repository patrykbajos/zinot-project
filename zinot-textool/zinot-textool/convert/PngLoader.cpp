//
// Created by patryk on 01.12.16.
//

#include "PngLoader.hpp"

#include <QFile>

namespace Zinot
{
namespace Textool
{

FREE_IMAGE_FORMAT PngLoader::getFiFormat(const QString fileName, QByteArray & byteArray)
{
   FIMEMORY fiMemStream;
   fiMemStream.data = byteArray.data();
   FREE_IMAGE_FORMAT fiFormat = FreeImage_GetFileTypeFromMemory(&fiMemStream);

   if (fiFormat == FIF_UNKNOWN)
   {
      std::cerr << "[ERROR] Could not get file format: " << fileName.toStdString() << std::endl;
      return FIF_UNKNOWN;
   }

   return fiFormat;
}

bool PngLoader::isReadableFiFormat(FREE_IMAGE_FORMAT fiFormat)
{
   if ((fiFormat == FIF_PNG) && FreeImage_FIFSupportsReading(fiFormat))
      return true;

   std::cerr << "[ERROR] FreeImage can not read this image type." << std::endl;
   return false;
}

FIBITMAP * PngLoader::loadPng(const QString & inFile)
{
   QFile file(inFile);
   if (!file.open(QIODevice::ReadOnly))
   {
      std::cerr << "[ERROR] Qt cannot open file: " << inFile.toStdString() << std::endl;
      return nullptr;
   }
   QByteArray bytes = file.readAll();

   FREE_IMAGE_FORMAT fiFormat = getFiFormat(inFile, bytes);
   if (fiFormat == FIF_UNKNOWN)
      return nullptr;

   if (!isReadableFiFormat(fiFormat))
      return nullptr;

   FIMEMORY fiMemStream;
   fiMemStream.data = bytes.data();
   FIBITMAP * fiBitmap = FreeImage_LoadFromMemory(fiFormat, &fiMemStream);

   if (!fiBitmap)
   {
      std::cerr << "[ERROR] FreeImage cannot load image: " << inFile.toStdString() << std::endl;
      return nullptr;
   }

   if (!makeValidBpp(fiBitmap))
   {
      std::cerr << "[ERROR] Program cannot make valid BPP in image: " << inFile.toStdString() << std::endl;
      return nullptr;
   }

   return fiBitmap;
}

bool PngLoader::makeValidBpp(FIBITMAP *& fiBitmap)
{
   auto bpp = FreeImage_GetBPP(fiBitmap);
   if (bpp != 32)
   {
      FIBITMAP * bitmapConverted = FreeImage_ConvertTo32Bits(fiBitmap);


      if (bitmapConverted == nullptr)
      {
         std::cerr << "[ERROR] FreeImage can not convert image to 32bpp" << std::endl;
         return false;
      }

      // Swap
      FreeImage_Unload(fiBitmap);
      fiBitmap = bitmapConverted;
   }

   return true;
}
}
}