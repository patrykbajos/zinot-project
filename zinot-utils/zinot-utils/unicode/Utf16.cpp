//
// Created by patryk on 04.06.16.
//

#include "Utf16.hpp"

#include <zinot-utils/unicode/Utf32.hpp>

namespace Zinot
{
namespace Unicode
{

void utf16StrToEndian(Endian::Type inEndian, uint16_t * inData, Endian::Type outEndian)
{
   Endian endian;
   endian.strToEndian(inEndian, sizeof(*inData), utf16StrSize(inData), inData, outEndian);
}

void utf16StrToLocal(Endian::Type inEndian, uint16_t * inData)
{
   Endian endian;
   endian.strToLocal(inEndian, sizeof(*inData), utf16StrSize(inData), inData);
}

/////////////////////

bool utf16CharToUnicode(const uint16_t * inData, uint32_t & outData)
{
   // LowWord is LOCAL Endian
   uint16_t lowWord = inData[0];
   uint32_t inputBytesNum = getUtf16CharSize(lowWord);

   // If it's pure Unicode Code
   if (inputBytesNum == 2)
   {
      outData = lowWord;
      return true;
   }

   // HighWord is Endian::LOCAL
   uint16_t highWord = inData[1];

   lowWord -= 0xD800;
   highWord -= 0xDC00;

   uint32_t unicode = 0;

   // Get first part
   unicode = lowWord;

   // Make place for 2nd part (always 10 bit number) and make OR 2nd part
   unicode <<= 10;
   unicode |= highWord;

   unicode += 0x10000;

   outData = unicode;
   return true;
}

uint32_t unicodeToUtf16Char(uint32_t inData, uint16_t * outData)
{
   uint32_t outBytesNum = getUtf16SizeFromUnicode(inData);

   if (outBytesNum == 2)
   {
      outData[0] = (uint16_t) inData;
      return 2;
   }

   if (outBytesNum == 4)
   {
      uint32_t unicode = inData;
      // Subtract 0x10000 to make 20bit number
      unicode -= 0x10000;

      uint16_t lowWord, highWord;

      // Get bits 0-9
      highWord = (uint16_t) unicode;
      highWord &= 0b1111111111;

      // Get bits 10-19
      unicode >>= 10;
      lowWord = (uint16_t) unicode;

      lowWord += 0xD800;
      highWord += 0xDC00;

      outData[0] = lowWord;
      outData[1] = highWord;

      return 4;
   }

   return 0;
}

/////////////////////

uint32_t getUtf16CharSize(const uint16_t inData)
{
   // Is in range of 0xD800 to 0xDFFF
   if ((inData >= 0xD800) && (inData <= 0xDFFF))
      return 4;
   else
      return 2;
}

uint32_t getUtf16SizeFromUnicode(uint32_t inData)
{
   // If in range of 0xD800 and 0xDFFF (special range for encoding)
   // or out of uint16_t range
   // means that is encoded on 4 bytes
   if (inData > 0xFFFF)
      return 4;
   if ((inData >= 0xD800) && (inData <= 0xDFFF))
      return 4;

   return 2;
}

//////////////////////

uint32_t getUnicodeStrSizeFromUtf16Str(const uint16_t * inData)
{
   return (getUtf16LettersNum(inData) * 4);
}

uint32_t getUtf16StrSizeFromUnicodeStr(const uint32_t * inData)
{
   uint32_t outUtfStrLen = 0;
   uint32_t uniStrRemained = utf32StrSize(inData);
   uint32_t uniStrIt = 0;

   //Dopuki nie wykroczy poza zakres tablicy i będą dane do przeczytania > 0
   while ((4 <= uniStrRemained) && (uniStrRemained > 0))
   {
      outUtfStrLen += getUtf16SizeFromUnicode(inData[uniStrIt]);

      ++uniStrIt;
      uniStrRemained -= 4;
   }

   return outUtfStrLen;
}

//////////////////////

uint32_t utf16StrSize(const uint16_t * inData)
{
   const uint8_t codeUnitLen = sizeof(uint16_t);
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

uint32_t getUtf16LettersNum(const uint16_t * inData)
{
   uint32_t utfStrSize = utf16StrSize(inData);

   const void * inDataGeneric = inData;
   uint32_t utfStrOffset = 0;
   uint32_t utfLettersNum = 0;
   while (utfStrSize)
   {
      uint16_t * charPtr = (uint16_t *) (inDataGeneric + utfStrOffset);
      uint32_t utfCharSize = getUtf16CharSize(*charPtr);

      if (utfCharSize > utfStrSize)
         break;

      utfStrOffset += utfCharSize;
      utfStrSize -= utfCharSize;
      ++utfLettersNum;
   }

   return utfLettersNum;
}

uint32_t getUtf16LetterOffset(const uint16_t * inData, uint32_t it)
{
   const void * inDataGeneric = inData;

   uint32_t utfStrSize = utf16StrSize(inData);
   uint32_t utfStrOffset = 0;

   while ((utfStrSize >= sizeof(uint16_t)) && (it > 0))
   {
      uint16_t * charPtr = (uint16_t *) (inDataGeneric + utfStrOffset);
      uint32_t utfFullLen = getUtf16CharSize(*charPtr);

      if (utfFullLen > utfStrSize)
         break;

      utfStrOffset += utfFullLen;
      utfStrSize -= utfFullLen;
      --it;
   }

   // If end of string and didn't get expected letter
   if (it != 0)
      return 0;

   return utfStrOffset;
}

///////////////////////

void utf16StrToUnicodeStr(const uint16_t * inData, uint32_t * outData)
{
   const void * inDataGeneric = inData;
   uint32_t utfStrRemainedBytes = utf16StrSize(inData);
   uint32_t utfStrOffset = 0;
   uint32_t utfCharSize = 0;

   uint32_t uniStrIt = 0;

   while (utfStrRemainedBytes > 0)
   {
      const uint16_t * charPtr = (uint16_t *) (inDataGeneric + utfStrOffset);
      utfCharSize = getUtf16CharSize(*charPtr);

      if (utfCharSize > utfStrRemainedBytes)
         break;

      utf16CharToUnicode(charPtr, outData[uniStrIt]);

      utfStrOffset += utfCharSize;
      utfStrRemainedBytes -= utfCharSize;
      ++uniStrIt;
   }
}

void unicodeStrToUtf16Str(const uint32_t * inData, uint16_t * outData)
{
   const void * outDataGeneric = outData;
   uint32_t utfStrOffset = 0;
   uint32_t uniCharsNum = getUtf32LettersNum(inData);

   for (uint32_t uniStrIt = 0; uniStrIt < uniCharsNum; ++uniStrIt)
   {
      // Convert Unicode to UTF and get encoded size from return value
      uint32_t utfEncodedCharSize = unicodeToUtf16Char(inData[uniStrIt], (uint16_t *) (outDataGeneric + utfStrOffset));

      utfStrOffset += utfEncodedCharSize;
   }
}
}
}