//
// Created by patryk on 15.06.16.
//
#include <gtest/gtest.h>

#include <zinot-utils/unicode/Unicode.hpp>
#include <zinot-utils/Endian.hpp>

#define _UTF8_STR { 0b11100111, 0b10110101, 0b10110001,\
0b11100100, 0b10111000, 0b10000000,\
0b11100111, 0b10100010, 0b10111100, 0 }
#define _UTF16_STR { 0x7D71, 0x4E00, 0x78BC, 0}
#define _UTF16_STR_INV { 0x717D, 0x004E, 0xBC78, 0}
#define _UTF32_STR { 0x00007D71, 0x00004E00, 0x000078BC, 0}
#define _UTF32_STR_INV { 0x717D0000, 0x004E0000, 0xBC780000, 0}

static const uint8_t utf8str[] = _UTF8_STR;
static const uint16_t utf16str[] = _UTF16_STR;
static const uint16_t utf16str_inv[] = _UTF16_STR_INV;
static const uint32_t utf32str[] = _UTF32_STR;
static const uint32_t utf32str_inv[] = _UTF32_STR_INV;

class UnicodeTest : public ::testing::Test
{
   Zinot::Endian endian;
};

TEST_F(UnicodeTest, utfStrToEndian)
{
   /*uint16_t u16inv[] = _UTF16_STR_INV;
   Zinot::Unicode::utfStrToEndian(Zinot::Unicode::UTF16, Zinot::Endian::BE, u16inv, Zinot::Endian::LE);

   EXPECT_EQ(0, std::memcmp(u16inv, utf16str, sizeof(u16inv)));*/
}

TEST_F(UnicodeTest, utfStrToLocal)
{ }

TEST_F(UnicodeTest, utfCharToUnicode)
{ }

TEST_F(UnicodeTest, unicodeToUtfChar)
{ }

TEST_F(UnicodeTest, getUtfCharSize)
{ }

TEST_F(UnicodeTest, getUtfSizeFromUnicode)
{ }

TEST_F(UnicodeTest, getUnicodeStrSizeFromUtfStr)
{ }

TEST_F(UnicodeTest, getUtfStrSizeFromUnicodeStr)
{ }

TEST_F(UnicodeTest, utfStrSize)
{ }

TEST_F(UnicodeTest, getLettersNum)
{
   EXPECT_EQ(4, Zinot::Unicode::getLettersNum(Zinot::Unicode::UTF8, utf8str));
   EXPECT_EQ(4, Zinot::Unicode::getLettersNum(Zinot::Unicode::UTF8, utf8str));
   EXPECT_EQ(4, Zinot::Unicode::getLettersNum(Zinot::Unicode::UTF8, utf8str));
}

TEST_F(UnicodeTest, getLetterOffset)
{ }

TEST_F(UnicodeTest, utfStrToUnicodeStr)
{ }

TEST_F(UnicodeTest, unicodeStrToUtfStr)
{ }