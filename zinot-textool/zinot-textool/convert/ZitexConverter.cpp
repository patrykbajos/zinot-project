//
// Created by patryk on 24.04.16.
//

#include "ZitexConverter.hpp"

#include <squish/squish.h>
#include <zinot-utils/zitex/Reader.hpp>

namespace Zinot
{
namespace Textool
{
bool ZitexConverter::convert(const QString & inFileName, const ConfigDao & configuration)
{
   auto inFileNameStdStr = inFileName.toStdString();

   Zitex::Reader reader;
   Zitex::Reader::Data data;

   reader.readFromFile(inFileNameStdStr, data);

   for (uint32_t it = 0; it < data.header->texImagesNum; ++it)
   {
      Zitex::TexImageHeader * texImageHeader = data.texImages[it].header;

      if (texImageHeader->level == 0)
      {
         auto width = texImageHeader->width;
         auto height = texImageHeader->height;

         FIBITMAP * fiBitmap = FreeImage_Allocate(width, height, 32);

         squish::DecompressImage(FreeImage_GetBits(fiBitmap), width, height, data.texImages[it].data,
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