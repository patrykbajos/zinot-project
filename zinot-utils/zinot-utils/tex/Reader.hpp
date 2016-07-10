//
// Created by patryk on 14.02.16.
//

#ifndef ZINOTPROJECT_TEXREADER_HPP
#define ZINOTPROJECT_TEXREADER_HPP

#include <string>
#include <vector>
#include <memory>

#include <zinot-utils/tex/Header.hpp>
#include <zinot-utils/tex/TexImageHeader.hpp>
#include <zinot-utils/Endian.hpp>

namespace Zinot
{
namespace Tex
{
class Reader
{

public:
   struct Data
   {
      // All data
      std::unique_ptr<uint8_t[]> rawData;
      uint64_t rawDataLength;

      struct TexImage
      {
         TexImageHeader * header;
         void * data;
      };

      // Pointers to data in rawData
      Header * header;
      std::unique_ptr<TexImage[]> texImage;
   };

   bool readFromFile(const std::string & fileName, Data & outData);
private:
   bool matchData(Data & outData);
   bool matchHeader(Data & outData, Endian::Type & fileEndian);
   bool matchTexImageHeadersAndData(Data & outData, Endian::Type fileEndian);
};
}
}

#endif //ZINOTPROJECT_TEXREADER_HPP
