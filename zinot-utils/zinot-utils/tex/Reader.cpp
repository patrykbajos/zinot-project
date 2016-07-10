//
// Created by patryk on 14.02.16.
//

#include "Reader.hpp"

#include <QString>
#include <QFile>

namespace Zinot
{
namespace Tex
{
bool Reader::readFromFile(const std::string & fileName, Data & outData)
{
   QFile file(QString::fromStdString(fileName));

   if (!file.open(QIODevice::ReadOnly))
      return false;

   auto fileSize = file.size();
   outData.rawDataLength = (uint64_t) fileSize;
   outData.rawData.reset(new uint8_t[fileSize]);

   file.read((char *) outData.rawData.get(), fileSize);
   file.close();

   matchData(outData);

   return true;
}

bool Reader::matchData(Data & outData)
{
   if (outData.rawData == nullptr)
      return false;

   Endian::Type fileEndian;
   // Returns in fileEndian initial file endian, matches header endian
   matchHeader(outData, fileEndian);

   // Reads data from header then before we must match header endian
   matchTexImageHeadersAndData(outData, fileEndian);

   return true;
}

bool Reader::matchHeader(Data & outData, Endian::Type & fileEndian)
{
   if (outData.rawDataLength < TEX_HEADER_SIZE)
      return false;

   // Bind pointer to header equals to begin of file
   outData.header = (Header *) outData.rawData.get();

   fileEndian = outData.header->getEndian();
   // Convert to local (UNKNOWN) endian
   outData.header->toEndian(Endian::LOCAL);

   return true;
}

bool Reader::matchTexImageHeadersAndData(Data & outData, Endian::Type fileEndian)
{
   // TODO: Wyjscie poza zakres danych | Array out of range
   uint32_t texImagesNum = outData.header->texImagesNum;
   outData.texImage.reset(new Data::TexImage[texImagesNum]);

   // Array of TexImageHeaders begins after file header (with fixed size)
   // TexImages data begin after all TexImageHeaders (with size * number)
   void * fileBegin = outData.rawData.get();
   void * tiHeaderPtr = fileBegin + TEX_HEADER_SIZE;
   void * tiDataPtr = tiHeaderPtr + (TEX_TEXIMAGEHEADER_SIZE * texImagesNum);

   for (uint32_t it = 0, tiDataOffset = 0, tiHeaderOffset = 0;
        it < texImagesNum; ++it)
   {
      // Each of TexImageHeader are placed in regular distance amount of TEX_TEXIMAGEHEADER_SIZE
      // tiHeaderOffset is multiple of TEX_TEXIMAGEHEADER_SIZE
      TexImageHeader * tiHeader = (TexImageHeader *) (tiHeaderPtr + tiHeaderOffset);
      // UNKNOWN means local machine endian
      tiHeader->toEndian(fileEndian, Endian::LOCAL);

      // tiDataOffset has irregular amount.
      // Its amount is in size of all previous data (taken from tiHeaders)
      void * tiData = tiDataPtr + tiDataOffset;

      outData.texImage[it].header = tiHeader;
      outData.texImage[it].data = tiData;

      // Add apprioprate offset amount size of read data.
      tiHeaderOffset += TEX_TEXIMAGEHEADER_SIZE;
      tiDataOffset += tiHeader->imageSize;
   }

   return true;
}
}
}
