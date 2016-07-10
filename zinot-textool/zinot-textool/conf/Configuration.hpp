//
// Created by patryk on 09.03.16.
//

#ifndef ZINOTPROJECT_CONFROOT_HPP
#define ZINOTPROJECT_CONFROOT_HPP

#include <zinot-textool/conf/GlBindTexture.hpp>
#include <zinot-textool/conf/GlTexImage.hpp>
#include <zinot-textool/conf/GlTexParameter.hpp>
#include <zinot-textool/conf/LayersNamePatterns.hpp>
#include <FreeImage.h>

class QJsonObject;

namespace Zinot
{
namespace Textool
{
class Configuration
{
private:
   bool compressed;
   FREE_IMAGE_FILTER mipmapFilter;
   GlBindTexture glBindTexture;
   GlTexImage glTexImage;
   GlTexParameter glTexParameter;
   LayersNamePatterns layersNamePatterns;
public:
   bool fromJsonObject(QJsonObject const & jsonObj);

   bool isCompressed() const
   { return compressed; }

   const GlBindTexture & getGlBindTexture() const
   { return glBindTexture; }

   const GlTexImage & getGlTexImage() const
   { return glTexImage; }

   const GlTexParameter & getGlTexParameter() const
   { return glTexParameter; }

   const LayersNamePatterns & getLayersNamePatterns() const
   { return layersNamePatterns; }

   FREE_IMAGE_FILTER getMipmapFilter() const
   { return mipmapFilter; }
};
}
}

#endif //ZINOTPROJECT_CONFROOT_HPP
