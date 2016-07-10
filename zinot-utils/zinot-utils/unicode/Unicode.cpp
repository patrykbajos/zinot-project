#include "Unicode.hpp"

#include <zinot-utils/unicode/Utf8.hpp>
#include <zinot-utils/unicode/Utf16.hpp>
#include <zinot-utils/unicode/Utf32.hpp>

namespace Zinot
{
namespace Unicode
{

void utfStrToEndian(Encoding inUTF, Endian::Type inEndian, void * inData, Endian::Type outEndian)
{
   if (!inData)
      return;

   if (inUTF == UTF16)
      utf16StrToEndian(inEndian, (uint16_t *) inData, outEndian);
   if (inUTF == UTF32)
      utf32StrToEndian(inEndian, (uint32_t *) inData, outEndian);
}

void utfStrToLocal(Encoding inUTF, Endian::Type inEndian, void * inData)
{
   if (!inData)
      return;

   if (inUTF == UTF16)
      utf16StrToLocal(inEndian, (uint16_t *) inData);
   if (inUTF == UTF32)
      utf32StrToLocal(inEndian, (uint32_t *) inData);
}

bool utfCharToUnicode(Encoding inUTF, const void * inData, uint32_t & outData)
{
   if (!outData)
      return NULL;

   if (inUTF == UTF8)
      return utf8CharToUnicode((uint8_t *) inData, outData);
   if (inUTF == UTF16)
      return utf16CharToUnicode((uint16_t *) inData, outData);
   if (inUTF == UTF32)
      return utf32CharToUnicode((uint32_t *) inData, outData);

   return NULL;
}

uint32_t unicodeToUtfChar(uint32_t inData, Encoding outUTF, void * outData)
{
   if (!outData)
      return NULL;

   if (outUTF == UTF8)
      return unicodeToUtf8Char(inData, (uint8_t *) outData);
   if (outUTF == UTF16)
      return unicodeToUtf16Char(inData, (uint16_t *) outData);
   if (outUTF == UTF32)
      return unicodeToUtf32Char(inData, (uint32_t *) outData);

   return NULL;
}

uint32_t getUtfCharSize(Encoding inUTF, const void * inData)
{
   if (!inData)
      return NULL;

   if (inUTF == UTF8)
      return getUtf8CharSize(((uint8_t *) inData)[0]);
   if (inUTF == UTF16)
      return getUtf16CharSize(((uint16_t *) inData)[0]);
   if (inUTF == UTF32)
      return getUtf32CharSize();

   return NULL;
}

uint32_t getUtfSizeFromUnicode(uint32_t inData, Encoding outUTF)
{
   if (outUTF == UTF8)
      return getUtf8SizeFromUnicode(inData);
   if (outUTF == UTF16)
      return getUtf16SizeFromUnicode(inData);
   if (outUTF == UTF32)
      return getUtf32SizeFromUnicode();

   return NULL;
}

uint32_t getUnicodeStrSizeFromUtfStr(Encoding inUTF, const void * inData)
{
   if (!inData)
      return NULL;

   if (inUTF == UTF8)
      return getUnicodeStrSizeFromUtf8Str((uint8_t *) inData, false);
   if (inUTF == UTF16)
      return getUnicodeStrSizeFromUtf16Str((uint16_t *) inData);
   if (inUTF == UTF32)
      return getUnicodeStrLenFromUtf32Str((uint32_t *) inData);

   return NULL;
}

uint32_t getUtfStrSizeFromUnicodeStr(Encoding outUTF, const uint32_t * inData)
{
   if (!inData)
      return NULL;

   if (outUTF == UTF8)
      return getUtf8StrSizeFromUnicodeStr(inData);
   if (outUTF == UTF16)
      return getUtf16StrSizeFromUnicodeStr(inData);
   if (outUTF == UTF32)
      return getUtf32StrSizeFromUnicodeStr(inData);

   return NULL;
}

uint32_t utfStrSize(Encoding inUTF, const void * inData)
{
   if (!inData)
      return NULL;

   if (inUTF == UTF8)
      return utf8StrSize((uint8_t *) inData);
   if (inUTF == UTF16)
      return utf16StrSize((uint16_t *) inData);
   if (inUTF == UTF32)
      return utf32StrSize((uint32_t *) inData);

   return NULL;
}

uint32_t getLettersNum(Encoding inUTF, const void * inData)
{
   if (!inData)
      return NULL;

   if (inUTF == UTF8)
      return getUtf8LettersNum((uint8_t *) inData, false);
   if (inUTF == UTF16)
      return getUtf16LettersNum((uint16_t *) inData);
   if (inUTF == UTF32)
      return getUtf32LettersNum((uint32_t *) inData);

   return NULL;
}

uint32_t getLetterOffset(Encoding inUTF, const void * inData, uint32_t it)
{
   if (!inData)
      return NULL;

   if (it == 0)
      return 0;

   if (inUTF == UTF8)
      return getUtf8LetterOffset((uint8_t *) inData, it, false);
   if (inUTF == UTF16)
      return getUtf16LetterOffset((uint16_t *) inData, it);
   if (inUTF == UTF32)
      return getUtf32LetterOffset((uint32_t *) inData, it);

   return NULL;
}

void utfStrToUnicodeStr(Encoding inUTF, const void * inData, uint32_t * outData)
{
   if (!(inData && outData))
      return;

   if (inUTF == UTF8)
      return utf8StrToUnicodeStr((uint8_t *) inData, outData);
   if (inUTF == UTF16)
      return utf16StrToUnicodeStr((uint16_t *) inData, outData);
   if (inUTF == UTF32)
      return utf32StrToUnicodeStr((uint32_t *) inData, outData);
}

void unicodeStrToUtfStr(const uint32_t * inData, Encoding outUTF, void * outData)
{
   if (!(inData && outData))
      return;

   if (outUTF == UTF8)
      unicodeStrToUtf8Str(inData, (uint8_t *) outData);
   if (outUTF == UTF16)
      unicodeStrToUtf16Str(inData, (uint16_t *) outData);
   if (outUTF == UTF32)
      unicodeStrToUtf32Str(inData, (uint32_t *) outData);
}
}
}