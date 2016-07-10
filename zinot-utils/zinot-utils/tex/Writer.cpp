//
// Created by patryk on 17.02.16.
//

#include "Writer.hpp"

#include <QFile>
#include <memory>

namespace Zinot
{
namespace Tex
{
bool Writer::write(const std::string & fileName, const Data & inData)
{   // TODO: Endianness support
   QFile file(QString::fromStdString(fileName));

   if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
      return false;

   if (!file.resize(calculateOutSize(inData)))
   {
      file.close();
      return false;
   }

   // Write basic header
   file.write((char *) &inData.header, sizeof(Header));

   // Write tex images headers
   file.seek(TEX_HEADER_SIZE);
   for (uint32_t it = 0; it < inData.header.texImagesNum; ++it)
   {
      auto pos = file.pos();

      file.write((char *) &inData.texImageHeader[it], sizeof(TexImageHeader));

      pos += TEX_TEXIMAGEHEADER_SIZE;
      file.seek(pos);
   }

   // Write tex images data
   for (uint32_t it = 0; it < inData.header.texImagesNum; ++it)
   {
      GLuint dataSize = inData.texImageHeader[it].imageSize;

      file.write((char *) inData.texImageData[it], dataSize);
   }

   file.close();
   return true;
}

uint32_t Writer::calculateOutSize(const Data & inData)
{
   uint32_t size = 0;

   // Add header size
   size += TEX_HEADER_SIZE;

   // Add TexImages headers size
   auto texImagesNum = inData.header.texImagesNum;
   size += (texImagesNum * TEX_TEXIMAGEHEADER_SIZE);

   // Add TexImages data size
   for (uint32_t it = 0; it < texImagesNum; ++it)
   {
      size += inData.texImageHeader[it].imageSize;
   }

   return size;
}
}
}