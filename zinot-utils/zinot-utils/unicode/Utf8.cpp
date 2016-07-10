//
// Created by patryk on 04.06.16.
//

#include "Utf8.hpp"

#include <zinot-utils/unicode/Utf32.hpp>

namespace Zinot
{
namespace Unicode
{


bool utf8CharToUnicode(const uint8_t * inData, uint32_t & outData)
{
   if (!inData)
      return false;

   Endian endian;
   uint32_t inputBytesNum = getUtf8CharSize(inData[0]);

   // If input is ASCII (0-127) code (has 1 byte Size)
   if (inputBytesNum == 1)
   {
      outData = inData[0];
      return true;
   }

   uint32_t unicode = 0;

   // Cut bits informing about bytes num
   uint8_t firstElem = inData[0];
   firstElem <<= inputBytesNum;
   firstElem >>= inputBytesNum;

   // Get data from main byte to unicode variable
   unicode = firstElem;

   // Get data from additional bytes (10xxxxxx)
   // Iterate from 1 which is first additional byte iterator
   for (int it = 1; it < inputBytesNum; ++it)
   {
      // Make place for 6 data bits from additional byte
      unicode <<= 6;
      uint8_t additionalByte = inData[it];

      // Cut two last (6-7) helper bits
      additionalByte &= 0b00111111;
      // OR with remained bits (0-5)
      unicode |= additionalByte;
   }

   outData = unicode;

   return true;
}

uint32_t unicodeToUtf8Char(uint32_t inData, uint8_t * outData)
{
   uint32_t outBytesNum = getUtf8SizeFromUnicode(inData);

   // If input is pure ASCII code
   if (outBytesNum == 1)
   {
      outData[0] = (uint8_t) inData;
      return 1;
   }

   // Reverse iterate without byte 0.
   // Make additional bytes 10xxxxxx.
   // Put them from end to begin.
   uint32_t endIterator = (outBytesNum - 1);
   uint32_t tempUnicode = inData;
   for (uint32_t revIt = endIterator; revIt > 0; --revIt)
   {
      // Get youngest byte from Unicode.
      uint8_t byte = (uint8_t) tempUnicode;
      // Clear bits 6-7.
      byte &= 0b00111111;
      // Put in bits 6-7 inbormal bits 0b10.
      byte |= 0b10000000;

      outData[revIt] = byte;
      // Remove last 6 bits.
      tempUnicode >>= 6;
   }

   // Make main byte.
   uint8_t firstByte = 0b11111111;
   uint32_t firstByteDataBitsNum = (8 - outBytesNum);

   // Make place for data bits.
   firstByte >>= firstByteDataBitsNum;
   firstByte <<= firstByteDataBitsNum;

   // Last We >>= 6 unicode code.
   // So then in tempUnicode there are last bits which are in main byte.
   firstByte |= tempUnicode;

   outData[0] = firstByte;
   return outBytesNum;
}

////////////////////

uint32_t getUtf8CharSize(const uint8_t inData)
{
   uint8_t byte = inData;

   // Jesli UTF8 jest czystym kodem ASCII
   if (byte <= 127)
   {
      return 1;
   }
   else // Jesli sklada sie z kilku bajtow
   {
      uint8_t counter = 0, mask = 0b10000000;
      while (byte & mask)
      {
         ++counter;
         mask >>= 1;
      }

      // Zwraca liczbe jesynek na koncu bajtu
      return counter;
   }
}

uint32_t getUtf8SizeFromUnicode(uint32_t inData)
{
   // Jesli to kod ASCII
   if (inData <= 127)
   {
      return 1;
   }
   else // Jesli to kod unicode
   {
      // Obliczenie liczby bitow z unicode
      uint32_t tempUni = inData;
      uint32_t uniBitsNum = 0;
      while (tempUni)
      {
         tempUni >>= 1;
         ++uniBitsNum;
      }

      /* Liczba bitow z unicode w pierwszym bajcie to reszta z dzielenia przez 6
       * Po odjeciu od siedmiu liczby bitow w pierwszym bajcie otrzymamy liczbe bajtow
       * b0: 0b1110xxxx
       * Bits number (from unicode) in b0: 4
       * Bytes number: 7 - 4 = 3
       */
      uint32_t additionalUTF8Bytes = (uint32_t) (uniBitsNum / 6);
      uint32_t UTF8BytesNum = additionalUTF8Bytes + 1;

      return UTF8BytesNum;
   }
}

////////////////////

uint32_t getUnicodeStrSizeFromUtf8Str(const uint8_t * inData, bool onlyAscii)
{
   return (getUtf8LettersNum(inData, onlyAscii) * 4);
}

uint32_t getUtf8StrSizeFromUnicodeStr(const uint32_t * inData)
{
   uint32_t outUtfStrLen = 0;
   uint32_t uniStrRemained = utf32StrSize(inData);
   uint32_t uniStrIt = 0;

   //Dopuki nie wykroczy poza zakres tablicy i będą dane do przeczytania > 0
   while ((4 <= uniStrRemained) && (uniStrRemained > 0))
   {
      outUtfStrLen += getUtf8SizeFromUnicode(inData[uniStrIt]);

      ++uniStrIt;
      uniStrRemained -= 4;
   }

   return outUtfStrLen;
}

////////////////////

uint32_t utf8StrSize(const uint8_t * inData)
{
   uint32_t strIt = 0;
   uint32_t strLen = 0;

   while (inData[strIt] != 0)
   {
      strLen += ZINOT_UNICODE_UTF8_UNIT_SIZE;
      ++strIt;
   }

   strLen += ZINOT_UNICODE_UTF8_UNIT_SIZE; // Add terminator \0 size

   return strLen;
}

uint32_t getUtf8LettersNum(const uint8_t * inData, bool onlyAscii)
{
   uint32_t utfStrSize = utf8StrSize(inData);

   if (onlyAscii)
      return utfStrSize;

   const void * inDataGeneric = inData;
   uint32_t utfStrOffset = 0;
   uint32_t utfLettersNum = 0;
   while (utfStrSize)
   {
      uint8_t * selectedChar = (uint8_t *) (inDataGeneric + utfStrOffset);
      uint32_t utfCharSize = getUtf8CharSize(selectedChar[0]);

      if (utfCharSize > utfStrSize)
         break;

      utfStrOffset += utfCharSize;
      utfStrSize -= utfCharSize;
      ++utfLettersNum;
   }

   return utfLettersNum;
}

uint32_t getUtf8LetterOffset(const uint8_t * inData, uint32_t it, bool onlyAscii)
{
   const void * inDataGeneric = inData;

   uint32_t utfStrSize = utf8StrSize(inData);
   uint32_t utfStrOffset = 0;

   // If only ascii characters offset is equal to iterator
   if (onlyAscii)
   {
      // IF iterator is out of range
      if (it > (utfStrSize - 1))
         return 0;

      return it;
   }

   while ((utfStrSize >= ZINOT_UNICODE_UTF8_UNIT_SIZE) && (it > 0))
   {
      uint8_t * selectedChar = (uint8_t *) (inDataGeneric + utfStrOffset);
      uint32_t utfFullLen = getUtf8CharSize(selectedChar[0]);

      if (utfFullLen > utfStrSize)
         break;

      utfStrOffset += utfFullLen;
      utfStrSize -= utfFullLen;
      --it;
   }

   // If end of string and won't get expected letter
   if (it != 0)
      return 0;

   return utfStrOffset;
}

///////////////////////

void utf8StrToUnicodeStr(const uint8_t * inData, uint32_t * outData)
{
   const void * inDataGeneric = inData;
   uint32_t utfStrRemainedBytes = utf8StrSize(inData);
   uint32_t utfStrOffset = 0;
   uint32_t utfCharSize = 0;

   uint32_t uniStrIt = 0;

   while (utfStrRemainedBytes > 0)
   {
      const uint8_t * selectedChar = (uint8_t *) (inDataGeneric + utfStrOffset);
      utfCharSize = getUtf8CharSize(selectedChar[0]);

      if (utfCharSize > utfStrRemainedBytes)
         break;

      utf8CharToUnicode(selectedChar, outData[uniStrIt]);

      utfStrOffset += utfCharSize;
      utfStrRemainedBytes -= utfCharSize;
      ++uniStrIt;
   }
}

void unicodeStrToUtf8Str(const uint32_t * inData, uint8_t * outData)
{
   const void * outDataGeneric = outData;
   uint32_t utfStrOffset = 0;
   uint32_t uniCharsNum = getUtf32LettersNum(inData);

   for (uint32_t uniStrIt = 0; uniStrIt < uniCharsNum; ++uniStrIt)
   {
      // Convert Unicode to UTF and get encoded size from return value
      uint32_t utfEncodedCharSize = unicodeToUtf8Char(inData[uniStrIt], (uint8_t *) (outDataGeneric + utfStrOffset));

      utfStrOffset += utfEncodedCharSize;
   }
}
}
}