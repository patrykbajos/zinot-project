//
// Created by patryk on 17.02.16.
//

#include "Writer.hpp"

#include <QFile>

namespace Zitex
{

bool Writer::write(const std::string & fileName, const Data & inData)
{
   QFile file(QString::fromStdString(fileName));

   if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
      return false;

   if (!file.resize(calculateOutSize(inData)))
   {
      file.close();
      return false;
   }

   // Write file header
   file.write((char *) &inData.header, sizeof(FileHeader));

   // Write zitex images headers
   file.seek(ZITEX_FILEHEADER_SIZE);
   for (uint32_t it=0; it < inData.header.texImagesNum; ++it)
   {
      auto ptr = file.pos();

      file.write((char *) &inData.texImageHeaders[it], sizeof(TexImageHeader));

      ptr += ZITEX_TEXIMAGEHEADER_SIZE;
      file.seek(ptr);
   }

   // Write zitex images data
   for (uint32_t it = 0; it < inData.header.texImagesNum; ++it)
   {
      GLuint dataSize = inData.texImageHeaders[it].imageSize;
      file.write((char *) inData.texImageData[it].get(), dataSize);
   }

   file.close();
   return true;
}

uint32_t Writer::calculateOutSize(const Data & inData)
{
   uint32_t size = 0;

   // Add file header size
   size += ZITEX_FILEHEADER_SIZE;

   // Add TexImages headers size
   uint32_t tiNum = inData.header.texImagesNum;
   size += (tiNum * ZITEX_TEXIMAGEHEADER_SIZE);

   // Add TexImages data size
   for (uint32_t it=0; it < tiNum; ++it)
      size += inData.texImageHeaders[it].imageSize;

   return size;
}

}