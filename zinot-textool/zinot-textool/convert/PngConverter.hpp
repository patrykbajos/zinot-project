//
// Created by patryk on 13.03.16.
//

#ifndef ZINOTENGINEPROJECT_PNGCONVERTER_HPP
#define ZINOTENGINEPROJECT_PNGCONVERTER_HPP

#ifdef _WIN32
#include <windows.h>
#endif
#include <FreeImage.h>
#include <vector>
#include <memory>

#include <zinot-textool/convert/Converter.hpp>
#include <zinot-textool/convert/Mipmap.hpp>

class QString;

namespace Zinot
{
namespace Textool
{
class PngConverter : public Converter
{
protected:
   bool generateMipmaps(FIBITMAP * fiBitmap, const ConfigDao & config,
                        std::vector<Mipmap> & mipmaps) const;
   bool compressMipmaps(std::vector<Mipmap> & mipmaps, const ConfigDao & config) const;
   QString generateOutName(const QString & inFilePath, const ConfigDao & config) const;
   bool writeToTex(const std::vector<Mipmap> & mipmaps, const ConfigDao & config,
                   QString const & outFilePath) const;
public:
   virtual bool convert(const QString & inFilePath, const ConfigDao & config) override;
};
}
}

#endif //ZINOTENGINEPROJECT_PNGCONVERTER_HPP
