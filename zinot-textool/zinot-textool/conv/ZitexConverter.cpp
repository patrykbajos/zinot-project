//
// Created by patryk on 24.04.16.
//

#include "ZitexConverter.hpp"

#include <zinot-utils/zitex/Reader.hpp>
#include <squish/squish.h>

namespace Zinot
{
namespace Textool
{
bool ZitexConverter::convert(const QString & inFileName, const Configuration & configuration)
{
   auto inFileNameStdStr = inFileName.toStdString();

   Tex::Reader reader;
   Tex::Reader::Data data;

   reader.readFromFile(inFileNameStdStr, data);

   for (uint32_t it = 0; it < data.header->texImagesNum; ++it)
   {
      Tex::TexImageHeader * texImageHeader = data.texImage[it].header;

      if (texImageHeader->level == 0)
      {
         auto width = texImageHeader->width;
         auto height = texImageHeader->height;

         FIBITMAP * fiBitmap = FreeImage_Allocate(width, height, 32);

         squish::DecompressImage(FreeImage_GetBits(fiBitmap), width, height, data.texImage[it].data,
                                 data.header->squishFlags);

         // section(".", 0, -2) copyes from begin to 2nd section from end.
         // The first section from end is the extension

         std::string outFileNameStdStr = inFileName.section(".", 0, -2).append(".png").toStdString();

         FreeImage_FlipVertical(fiBitmap);
         FreeImage_Save(FIF_PNG, fiBitmap, outFileNameStdStr.c_str());

         FreeImage_Unload(fiBitmap);
      }
   }
}
}
};