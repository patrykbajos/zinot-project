//
// Created by patryk on 14.02.16.
//

#ifndef ZINOTPROJECT_TEXREADER_HPP
#define ZINOTPROJECT_TEXREADER_HPP

#include <string>
#include <vector>
#include <memory>

#include <zinot-utils/zitex/FileHeader.hpp>
#include <zinot-utils/zitex/TexImageHeader.hpp>
#include <zinot-utils/Endian.hpp>

namespace Zitex
{

class Reader
{
public:
   struct Data
   {
      struct TexImage
      {
         TexImageHeader * header;
         uint8_t * data;
      };

      // Pointers to data in rawData
      // Owner of header is rawData. !DO NOT FREE header!
      std::vector<uint8_t> rawData;
      FileHeader * header;
      std::vector<TexImage> texImages;
   };

   bool readFromFile(const std::string & fileName, Data & outData);
private:
   bool matchData(Data & outData);
   bool matchFileHeader(Data & outData, Zinot::Endian::Type & fileEndian);
   bool matchTexImageHeaders(Data & outData, Zinot::Endian::Type fileEndian);
   bool matchTexImagesData(Data & outData, Zinot::Endian::Type fileEndian);
};

}

#endif //ZINOTPROJECT_TEXREADER_HPP
