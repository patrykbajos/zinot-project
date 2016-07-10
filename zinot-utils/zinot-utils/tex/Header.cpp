//
// Created by patryk on 14.02.16.
//

#include "Header.hpp"
#include <zinot-utils/Endian.hpp>

namespace Zinot
{
namespace Tex
{
void Header::toEndian(Endian::Type outEndian)
{
   Endian endian;
   Endian::Type inEndian = getEndian();

   if (outEndian == Endian::LOCAL)
      outEndian = endian.getLocalEndian();

   endian.toEndian(inEndian, sizeof(version), &version, outEndian);
   endian.toEndian(inEndian, sizeof(target), &target, outEndian);

   endian.toEndian(inEndian, sizeof(LOD_BIAS), &LOD_BIAS, outEndian);
   endian.toEndian(inEndian, sizeof(MIN_FILTER), &MIN_FILTER, outEndian);
   endian.toEndian(inEndian, sizeof(MAG_FILTER), &MAG_FILTER, outEndian);
   endian.toEndian(inEndian, sizeof(MIN_LOD), &MIN_LOD, outEndian);
   endian.toEndian(inEndian, sizeof(MAX_LOD), &MAX_LOD, outEndian);
   endian.toEndian(inEndian, sizeof(MAX_LEVEL), &MAX_LEVEL, outEndian);
   endian.toEndian(inEndian, sizeof(WRAP_S), &WRAP_S, outEndian);
   endian.toEndian(inEndian, sizeof(WRAP_T), &WRAP_T, outEndian);
   endian.toEndian(inEndian, sizeof(WRAP_R), &WRAP_R, outEndian);

   endian.toEndian(inEndian, sizeof(internalFormat), &internalFormat, outEndian);
   endian.toEndian(inEndian, sizeof(format), &format, outEndian);
   endian.toEndian(inEndian, sizeof(type), &type, outEndian);

   endian.toEndian(inEndian, sizeof(texImagesNum), &texImagesNum, outEndian);

   endian.toEndian(inEndian, sizeof(squishFlags), &squishFlags, outEndian);

   if (outEndian == Endian::Type::LE)
      isLE = 1;
   else
      isLE = 0;
}

Endian::Type Header::getEndian()
{
   if (isLE)
      return Endian::Type::LE;
   else
      return Endian::Type::BE;
}
}
}