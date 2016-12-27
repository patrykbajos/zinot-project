//
// Created by patryk on 04.06.16.
//

#include "Utf32.hpp"

namespace Zinot
{
namespace Unicode
{

void utf32StrToEndian(Endian::Type inEndian, uint32_t * inData, Endian::Type outEndian)
{
   Endian endian;
   endian.strToEndian(inEndian, sizeof(*inData), utf32StrSize(inData), inData, outEndian);
}

void utf32StrToLocal(Endian::Type inEndian, uint32_t * inData)
{
   Endian endian;
   endian.strToLocal(inEndian, sizeof(*inData), utf32StrSize(inData), inData);
}

bool utf32CharToUnicode(const uint32_t * inData, uint32_t & outData)
{
   outData = *inData;

   return true;
}

uint32_t unicodeToUtf32Char(uint32_t inData, uint32_t * outData)
{
   outData[0] = inData;

   return 4;
}

uint32_t utf32StrSize(const uint32_t * inData)
{
   const uint8_t codeUnitLen = sizeof(uint32_t);
   uint32_t strIt = 0;
   uint32_t strLen = 0;

   while (inData[strIt] != 0)
   {
      strLen += codeUnitLen;
      ++strIt;
   }

   strLen += codeUnitLen; // Add terminator \0 size

   return strLen;
}

uint32_t getUtf32LetterOffset(const uint32_t * inData, uint32_t it)
{
   uint32_t utfLettersNum = getUtf32LettersNum(inData);

   if (it > (utfLettersNum - 1))
      return 0;

   return (it * sizeof(uint32_t));
}

void utf32StrToUnicodeStr(const uint32_t * inData, uint32_t * outData)
{
   std::memcpy(outData, inData, utf32StrSize(inData));
}

void unicodeStrToUtf32Str(const uint32_t * inData, uint32_t * outData)
{
   std::memcpy(outData, inData, utf32StrSize(inData));
}
}
}