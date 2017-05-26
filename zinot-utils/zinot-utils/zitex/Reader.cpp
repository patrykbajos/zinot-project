//
// Created by patryk on 14.02.16.
//

#include "Reader.hpp"

#include <QFile>

namespace Zitex
{

bool Reader::readFromFile(const std::string & fileName, Data & outData)
{
   QFile file(QString::fromStdString(fileName));

   if (!file.open(QIODevice::ReadOnly))
      return false;

   auto fileSize = file.size();
   outData.rawData.resize((unsigned long) fileSize);
   file.read((char *) outData.rawData.data(), fileSize);

   file.close();
   return matchData(outData);
}

bool Reader::matchData(Data & outData)
{
   Zinot::Endian::Type fileEndian;
   // Returns in fileEndian initial file endian, matches header endian
   if(!matchFileHeader(outData, fileEndian))
      return false;

   if(!matchTexImageHeaders(outData, fileEndian))
      return false;

   return matchTexImagesData(outData, fileEndian);
}

bool Reader::matchFileHeader(Data & outData, Zinot::Endian::Type & fileEndian)
{
   if (outData.rawData.size() < ZITEX_FILEHEADER_SIZE)
      return false;

   // Bind pointer to header equals to begin of file
   outData.header = (FileHeader *) outData.rawData.data();

   fileEndian = outData.header->getEndian();
   outData.header->toEndian(Zinot::Endian::LOCAL);

   return true;
}

bool Reader::matchTexImageHeaders(Data & outData, Zinot::Endian::Type fileEndian)
{
   /* File Structure:
    * * FileHeader with size of [ZITEX_FILEHEADER_SIZE] at address [0]
    * * TexImageHeaders with size of [ZITEX_TEXIMAGEHEADER_SIZE] at address [ZITEX_FILEHEADER_SIZE]
    * * TexImages data with dynamic size at address [TexImageHeaders number * ZITEX_TEXIMAGEHEADER_SIZE]
    *   TexImage data size is written in tiHeader->imageSize
    */

   void * fileBegin = outData.rawData.data();
   void * tiHeadersBegin = fileBegin + ZITEX_FILEHEADER_SIZE;
   auto tiNum = outData.header->texImagesNum;
   auto tiHeadersSize = ZITEX_TEXIMAGEHEADER_SIZE * tiNum;

   // Data size validation
   if(outData.rawData.size() < (ZITEX_FILEHEADER_SIZE + tiHeadersSize))
      return false;

   for (uint32_t it = 0; it < tiNum; ++it)
   {
      TexImageHeader * tiHeader = (TexImageHeader *) (tiHeadersBegin + (ZITEX_TEXIMAGEHEADER_SIZE * it));
      tiHeader->toEndian(fileEndian, Zinot::Endian::LOCAL);
      outData.texImages[it].header = tiHeader;
   }

   return true;
}

bool Reader::matchTexImagesData(Data & outData, Zinot::Endian::Type fileEndian)
{
   void * fileBegin = outData.rawData.data();
   uint32_t tiNum = outData.header->texImagesNum;
   uint32_t tiHeadersSize = tiNum * ZITEX_TEXIMAGEHEADER_SIZE;
   void * tiDataBegin = fileBegin + ZITEX_FILEHEADER_SIZE + tiHeadersSize;

   // Data size validation
   uint32_t tiDataSize = 0;
   for(uint32_t it=0; it < tiNum; ++it)
      tiDataSize += outData.texImages[it].header->imageSize;

   if(outData.rawData.size() < (ZITEX_FILEHEADER_SIZE + tiHeadersSize + tiDataSize))
      return false;

   for(uint32_t it=0, tiDataOffset=0; it < tiNum; ++it)
   {
      outData.texImages[it].data = (uint8_t *)(tiDataBegin + tiDataOffset);

      uint32_t tiDataSize = outData.texImages[it].header->imageSize;
      tiDataOffset += tiDataSize;
   }

   return true;
}

}
