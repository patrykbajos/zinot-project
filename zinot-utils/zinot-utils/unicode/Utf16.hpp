//
// Created by patryk on 04.06.16.
//

#ifndef ZINOTENGINEPROJECT_UTF16_HPP
#define ZINOTENGINEPROJECT_UTF16_HPP

#include <stdint.h>
#include <zinot-utils/Endian.hpp>

namespace Zinot
{
namespace Unicode
{

#define ZINOT_UNICODE_UTF16_UNIT_SIZE sizeof(uint16_t)

void utf16StrToEndian(Endian::Type inEndian, uint16_t * inData, Endian::Type outEndian);
void utf16StrToLocal(Endian::Type inEndian, uint16_t * inData);

bool utf16CharToUnicode(const uint16_t * inData, uint32_t & outData);
uint32_t unicodeToUtf16Char(uint32_t inData, uint16_t * outData);

uint32_t getUtf16CharSize(const uint16_t inData);
uint32_t getUtf16SizeFromUnicode(uint32_t inData);

uint32_t getUnicodeStrSizeFromUtf16Str(const uint16_t * inData);
uint32_t getUtf16StrSizeFromUnicodeStr(const uint32_t * inData);

uint32_t utf16StrSize(const uint16_t * inData);
uint32_t getUtf16LettersNum(const uint16_t * inData);
uint32_t getUtf16LetterOffset(const uint16_t * inData, uint32_t it);

void utf16StrToUnicodeStr(const uint16_t * inData, uint32_t * outData);
void unicodeStrToUtf16Str(const uint32_t * inData, uint16_t * outData);
}
}

#endif //ZINOTENGINEPROJECT_UTF16_HPP
