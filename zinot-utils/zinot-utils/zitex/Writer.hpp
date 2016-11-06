//
// Created by patryk on 17.02.16.
//

#ifndef ZINOTENGINEPROJECT_WRITER_HPP
#define ZINOTENGINEPROJECT_WRITER_HPP

#include <string>
#include <vector>
#include <memory>

#include <zinot-utils/zitex/FileHeader.hpp>
#include <zinot-utils/zitex/TexImageHeader.hpp>
#include <zinot-utils/Endian.hpp>

namespace Zitex
{

class Writer
{
public:
   struct Data
   {
      FileHeader header;
      std::vector<TexImageHeader> texImageHeaders;
      std::vector<std::unique_ptr<uint8_t[]>> texImageData;
   };

   bool write(const std::string & fileName, const Data & inData);

private:
   uint32_t calculateOutSize(const Data & writeData);
};

}

#endif //ZINOTENGINEPROJECT_WRITER_HPP
