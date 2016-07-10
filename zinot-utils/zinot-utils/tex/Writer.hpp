//
// Created by patryk on 17.02.16.
//

#ifndef ZINOTENGINEPROJECT_WRITER_HPP
#define ZINOTENGINEPROJECT_WRITER_HPP

#include <string>
#include <vector>

#include <zinot-utils/tex/Header.hpp>
#include <zinot-utils/tex/TexImageHeader.hpp>
#include <zinot-utils/Endian.hpp>

namespace Zinot
{
namespace Tex
{
class Writer
{
public:
   struct Data
   {
      Endian::Type outEndian;
      Header header;

      std::vector<TexImageHeader> texImageHeader;
      std::vector<const void *> texImageData;
   };

   bool write(const std::string & fileName, const Data & inData);

private:
   uint32_t calculateOutSize(const Data & writeData);
};
}
}

#endif //ZINOTENGINEPROJECT_WRITER_HPP
