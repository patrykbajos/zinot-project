#ifndef UTFTRANSLATOR_HPP_
#define UTFTRANSLATOR_HPP_

#include <math.h>
#include <stdint.h>
#include <cstring>

#include <zinot-utils/Endian.hpp>

namespace Zinot
{
namespace Unicode
{

enum Encoding
{
   UTF8, UTF16, UTF32
};

// TODO Make function converting UTF String to specified endian
void utfStrToEndian(Encoding inUTF, Endian::Type inEndian, void * inData, Endian::Type outEndian);
void utfStrToLocal(Encoding inUTF, Endian::Type inEndian, void * inData);

bool utfCharToUnicode(Encoding inUTF, const void * inData, uint32_t & outData);
uint32_t unicodeToUtfChar(uint32_t inData, Encoding outUTF, void * outData);

/**
 * @brief Returns full Size of encoded Code Point form first Code Unit
 *
 * @param inEnc Input encoding
 * @param inData Input data
 * @return Size of encoded Code Unit in bytes
 */
uint32_t getUtfCharSize(Encoding inUTF, const void * inData);

/**
 * @brief Returns output UTF Size from Unicode Code Point
 *
 * @param outEnc Output encoding
 * @param unicode Unicode Code Point
 * @return UTF Size from Unicode Code Point in bytes
 */
uint32_t getUtfSizeFromUnicode(uint32_t inData, Encoding outUTF);

/**
 * @brief Returns output Size (and storage requirements) of UTF String after decoding to Unicode Code Points
 *
 * @param inEnc Input encoding
 * @param inData Input data (Utf string terminated with Code Point 0)
 */
uint32_t getUnicodeStrSizeFromUtfStr(Encoding inUTF, const void * inData);

/**
 * @brief Returns Size in bytes after encoding Unicode String to UTF String
 *
 * @param outEnc Output encoding
 * @param num Input data Size in bytes
 * @param inData Input data (Unicode string terminated with Code Point 0)
 */
uint32_t getUtfStrSizeFromUnicodeStr(Encoding outUTF, const uint32_t * inData);

/**
 * @brief Oblicza długość w bajtach ciągu UTF zakończonych code point U+0000
 *
 * @param inEnc Kodowanie wejściowe
 * @param inData Dane wejściowe
 * @return Liczba bajtów w ciągu znaków UTF
 */
uint32_t utfStrSize(Encoding inUTF, const void * inData);

/**
 * @brief Oblicza liczbe znaków w ciągu UTF
 *
 * @param inUTF Kodowanie wejściowe
 * @param inData Dane wejściowe
 */
uint32_t getLettersNum(Encoding inUTF, const void * inData);

/**
 * @brief Returns offset in bytes of specified letter iteraror (the first letter is it = 0)
 *
 * @param inUTF Input encoding
 * @param inData Input data
 * @param it Letter iterator, the first is 0
 */
uint32_t getLetterOffset(Encoding inUTF, const void * inData, uint32_t it);

/**
 * @brief Converts UTF strinf to Unicode string
 *
 * @param inUTF Input encoding
 * @param inData Input data
 * @param outData Output data
 */
void utfStrToUnicodeStr(Encoding inUTF, const void * inData, uint32_t * outData);

/**
 * @brief Converts Unicode string to UTF string
 *
 * @param inData Input data
 * @param outUTF Output encoding
 * @param outData Output data
 */
void unicodeStrToUtfStr(const uint32_t * inData, Encoding outUTF, void * outData);
}
}

#endif /* UTFTRANSLATOR_HPP_ */
