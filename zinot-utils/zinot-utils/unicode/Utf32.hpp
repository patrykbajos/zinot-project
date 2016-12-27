//
// Created by patryk on 04.06.16.
//

#ifndef ZINOTENGINEPROJECT_UTF32_HPP
#define ZINOTENGINEPROJECT_UTF32_HPP

#include <stdint.h>
#include <zinot-utils/Endian.hpp>
#include <zinot-utils/unicode/Unicode.hpp>

namespace Zinot
{
namespace Unicode
{

#define ZINOT_UNICODE_UTF32_UNIT_SIZE sizeof(uint32_t)

void utf32StrToEndian(Endian::Type inEndian, uint32_t * inData, Endian::Type outEndian);
void utf32StrToLocal(Endian::Type inEndian, uint32_t * inData);

bool utf32CharToUnicode(const uint32_t * inData, uint32_t & outData);
uint32_t unicodeToUtf32Char(uint32_t inData, uint32_t * outData);

inline uint32_t getUtf32CharSize()
{ return 4; }

inline uint32_t getUtf32SizeFromUnicode()
{ return 4; };

// Forward declaration
uint32_t utf32StrSize(const uint32_t * inData);

inline uint32_t getUnicodeStrLenFromUtf32Str(const uint32_t * inData)
{ return utf32StrSize(inData); }

inline uint32_t getUtf32StrSizeFromUnicodeStr(const uint32_t * inData)
{ return utf32StrSize(inData); }

uint32_t utf32StrSize(const uint32_t * inData);

inline uint32_t getUtf32LettersNum(const uint32_t * inData)
{ return (utf32StrSize(inData) / 4); }

uint32_t getUtf32LetterOffset(const uint32_t * inData, uint32_t it);

void utf32StrToUnicodeStr(const uint32_t * inData, uint32_t * outData);
void unicodeStrToUtf32Str(const uint32_t * inData, uint32_t * outData);
}
}

#endif //ZINOTENGINEPROJECT_UTF32_HPP
