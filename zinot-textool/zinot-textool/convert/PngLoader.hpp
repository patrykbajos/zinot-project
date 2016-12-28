//
// Created by patryk on 01.12.16.
//

#ifndef ZINOT_PROJECT_PNGLOADER_HPP
#define ZINOT_PROJECT_PNGLOADER_HPP

#ifdef _WIN32
#include <windows.h>
#endif
#include <FreeImage.h>
#include <iostream>
#include <QString>

namespace Zinot
{
namespace Textool
{

class PngLoader
{
private:
   static FREE_IMAGE_FORMAT getFiFormat(const QString fileName, QByteArray & byteArray);
   static bool isReadableFiFormat(FREE_IMAGE_FORMAT fiFormat);
   static bool makeValidBpp(FIBITMAP *& fiBitmap);
public:
   static FIBITMAP * loadPng(const QString & inFile);
};
}
}

#endif //ZINOT_PROJECT_PNGLOADER_HPP
