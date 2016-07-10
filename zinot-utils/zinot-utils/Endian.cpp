//
// Created by patryk on 28.09.15.
//

#include "Endian.hpp"

#include <limits.h>
#include <stdint.h>
#include <functional>

#if CHAR_BIT != 8
#error "Error::Endian.cpp: unsupported char size"
#endif

namespace Zinot
{
static const Endian::EndianCheckUnion _host_order = {{0, 1, 2, 3}};

Endian::Endian()
{
   localEndian = (Type) _host_order.value;
}

void Endian::toLocal(Type inEndian, uint32_t elemSize, void * inData)
{
   if (!inData)
      return;

   if (inEndian == LOCAL)
      inEndian = getLocalEndian();

   if (inEndian != localEndian)
      swapBytesOrder(elemSize, inData);
}

void Endian::strToLocal(Type inEndian, uint32_t elemSize, uint32_t dataSize, void * inData)
{
   if (!inData)
      return;

   if (inEndian == LOCAL)
      return;
   if (inEndian == localEndian)
      return;

   uint32_t elemNum = (dataSize / elemSize);
   if ((elemNum * elemSize) != dataSize)
      return;

   for (uint32_t it = 0; it < elemNum; ++it)
   {
      toLocal(inEndian, elemSize, inData + (elemSize * it));
   }
}

void Endian::toEndian(Type inEndian, uint32_t elemSize, void * inData, Type outEndian)
{
   // Check pointer validity
   if (!inData)
      return;

   if (outEndian == LOCAL)
      toLocal(inEndian, elemSize, inData);

   if (inEndian == LOCAL)
      inEndian = getLocalEndian();

   if (inEndian != outEndian)
      swapBytesOrder(elemSize, inData);
}

void Endian::strToEndian(Type inEndian, uint32_t elemSize, uint32_t dataSize, void * inData, Type outEndian)
{
   if (!inData)
      return;

   if (inEndian == outEndian)
      return;

   uint32_t elemNum = (dataSize / elemSize);
   if ((elemNum * elemSize) != dataSize)
      return;

   for (uint32_t it = 0; it < elemNum; ++it)
   {
      toEndian(inEndian, elemSize, inData + (elemSize * it), outEndian);
   }
}

void Endian::swapBytesOrder(uint32_t elemSize, void * inData)
{
   if (!inData)
      return;

   if (elemSize > 1)
   {
      uint64_t halfIt = elemSize / 2;
      uint64_t reverseIt = elemSize - 1;
      uint8_t * ptrData = (uint8_t *) inData;

      for (uint64_t it = 0; it < halfIt; ++it, --reverseIt)
      {
         std::swap(ptrData[it], ptrData[reverseIt]);
      }
   }
}
}
