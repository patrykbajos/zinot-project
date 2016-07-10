//
// Created by patryk on 28.09.15.
//

#ifndef ZINOT_UTIL_ENDIAN_HPP
#define ZINOT_UTIL_ENDIAN_HPP

#include <stdint.h>

namespace Zinot
{
class Endian
{
public:
   enum Type
   {
      LOCAL,               ///< Local endian
      BE = 0x00010203ul,   ///< Little Endian
      LE = 0x03020100ul,   ///< Big Endian
      // PDP deprecated because it is on old unused computer
      // PDP = 0x01000302ul   ///< PDP Endian
   };

   union EndianCheckUnion
   {
      unsigned char bytes[4];
      uint32_t value;
   };

   Endian();
   void toLocal(Type inEndian, uint32_t elemSize, void * inData);
   void strToLocal(Type inEndian, uint32_t elemSize, uint32_t dataSize, void * inData);
   void toEndian(Type inEndian, uint32_t elemSize, void * inData, Type outEndian);
   void strToEndian(Type inEndian, uint32_t elemSize, uint32_t dataSize, void * inData, Type outEndian);
   void swapBytesOrder(uint32_t elemSize, void * inData);

   inline Type getLocalEndian()
   {
      return localEndian;
   }

private:
   Type localEndian;
};
}

#endif //ZINOT_ENDIANNESS_HPP
