#include <gtest/gtest.h>
#include <zinot-utils/Endian.hpp>
#include <cstring>

#define DSTR4 {1, 2, 3, 4}
#define DSTR4I {4, 3, 2, 1}
#define DSTR2 {1, 2}
#define DSTR2I {2, 1}
#define DSTR8 {1, 2, 3, 4, 5, 6, 7, 8}
#define DSTR8I {8, 7, 6, 5, 4, 3, 2, 1}

class EndianTest : public ::testing::Test
{
protected:
   Zinot::Endian endian;
};

TEST_F(EndianTest, swapBytes)
{
   uint8_t str4[] = DSTR4;
   uint8_t str4i[] = DSTR4I;
   uint8_t str2[] = DSTR2;
   uint8_t str2i[] = DSTR2I;
   uint8_t str8[] = DSTR8;
   uint8_t str8i[] = DSTR8I;

   endian.swapBytesOrder(2, str2i);
   endian.swapBytesOrder(4, str4i);
   endian.swapBytesOrder(8, str8i);

   EXPECT_EQ(0, std::memcmp(str2, str2i, 2));
   EXPECT_EQ(0, std::memcmp(str4, str4i, 4));
   EXPECT_EQ(0, std::memcmp(str8, str8i, 8));
}

TEST_F(EndianTest, getEndian)
{
#if __BYTE_ORDER == __LITTLE_ENDIAN
   EXPECT_EQ(Zinot::Endian::Type::LE, endian.getLocalEndian());
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
   EXPECT_EQ(Zinot::Endian::Type::BE, endian.getLocalEndian());
#endif
}