#include <gtest/gtest.h>
#include <zinot-utils/Endian.hpp>
#include <cstring>

#define dstr4 { 1, 2, 3, 4}
#define dstr4i { 4, 3, 2, 1}
#define dstr2 { 1, 2 }
#define dstr2i { 2, 1}
#define dstr8 {1,2,3,4,5,6,7,8}
#define dstr8i {8,7,6,5,4,3,2,1}

class EndianTest : public ::testing::Test
{
protected:
   Zinot::Endian endian;
};

TEST_F(EndianTest, swapBytes)
{
   uint8_t str4[] = dstr4;
   uint8_t str4i[] = dstr4i;
   uint8_t str2[] = dstr2;
   uint8_t str2i[] = dstr2i;
   uint8_t str8[] = dstr8;
   uint8_t str8i[] = dstr8i;

   //Zinot::Endian endian;

   endian.swapBytesOrder(2, str2);
   endian.swapBytesOrder(4, str4);
   endian.swapBytesOrder(8, str8);

   EXPECT_EQ(0, std::memcmp(str2, str2i, 2));
   EXPECT_EQ(0, std::memcmp(str4, str4i, 4));
   EXPECT_EQ(0, std::memcmp(str8, str8i, 8));

   EXPECT_EQ(Zinot::Endian::Type::LE, endian.getLocalEndian());
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