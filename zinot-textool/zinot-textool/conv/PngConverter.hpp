//
// Created by patryk on 13.03.16.
//

#ifndef ZINOTENGINEPROJECT_PNGCONVERTER_HPP
#define ZINOTENGINEPROJECT_PNGCONVERTER_HPP

#include <vector>
#include <memory>

#include <zinot-textool/conv/Converter.hpp>
#include <zinot-textool/conv/Mipmap.hpp>
#include <FreeImage.h>

class QString;

namespace Zinot
{
namespace Textool
{
class PngConverter : public Converter
{
protected:
   FREE_IMAGE_FORMAT getFiFormat(const char * inFile) const;
   bool isReadableFiFormat(FREE_IMAGE_FORMAT fiFormat) const;
   FIBITMAP * loadFiBitmap(const std::string & inFile, FREE_IMAGE_FORMAT fiFormat) const;
   bool makeValidBpp(FIBITMAP *& fiBitmap) const;
   bool flipVertically(FIBITMAP * fiBitmap) const;
   bool dibToRGBA(FIBITMAP * fiBitmap) const;

   int generateSquishFlags(const Configuration & configuration) const;
   bool generateMipMaps(FIBITMAP * fiBitmap, const Configuration & configuration,
                        std::vector<Mipmap> & mipmaps) const;
   bool compressImages(std::vector<Mipmap> & mipmaps, const Configuration & configuration) const;
   QString generateOutName(const QString & inFileName, const Configuration & configuration) const;
   bool writeToTex(const std::vector<Mipmap> & mipmaps, const Configuration & configuration,
                   QString const & outName) const;
public:
   virtual bool convert(const QString & inFileName, const Configuration & configuration) override;
};
}
}

#endif //ZINOTENGINEPROJECT_PNGCONVERTER_HPP
