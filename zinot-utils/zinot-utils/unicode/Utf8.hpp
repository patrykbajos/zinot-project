//
// Created by patryk on 04.06.16.
//

#ifndef ZINOTENGINEPROJECT_UTF8_HPP
#define ZINOTENGINEPROJECT_UTF8_HPP

#include <cstdint>
#include <cstdlib>

#include <zinot-utils/Endian.hpp>

namespace Zinot
{
namespace Unicode
{

#define ZINOT_UNICODE_UTF8_UNIT_SIZE sizeof(uint8_t)

bool utf8CharToUnicode(const uint8_t * inData, uint32_t & outData);
uint32_t unicodeToUtf8Char(uint32_t inData, uint8_t * outData);

uint32_t getUtf8CharSize(const uint8_t inData);
uint32_t getUtf8SizeFromUnicode(uint32_t inData);

uint32_t getUnicodeStrSizeFromUtf8Str(const uint8_t * inData, bool onlyAscii);
uint32_t getUtf8StrSizeFromUnicodeStr(const uint32_t * inData);

uint32_t utf8StrSize(const uint8_t * inData);
uint32_t getUtf8LettersNum(const uint8_t * inData, bool onlyAscii);
uint32_t getUtf8LetterOffset(const uint8_t * inData, uint32_t it, bool onlyAscii);

void utf8StrToUnicodeStr(const uint8_t * inData, uint32_t * outData);
void unicodeStrToUtf8Str(const uint32_t * inData, uint8_t * outData);
}
}

#endif //ZINOTENGINEPROJECT_UTF8_HPP
