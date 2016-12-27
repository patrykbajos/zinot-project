//
// Created by patryk on 09.03.16.
//

#ifndef ZINOTPROJECT_CONFROOT_HPP
#define ZINOTPROJECT_CONFROOT_HPP

#ifdef _WIN32
#include <windows.h>
#endif
#include <FreeImage.h>
#include <QJsonObject>

#include <zinot-textool/config/GlBindTextureDao.hpp>
#include <zinot-textool/config/GlTexImageDao.hpp>
#include <zinot-textool/config/GlTexParameterDao.hpp>
#include <zinot-textool/config/LayersNamePatternsDao.hpp>

namespace Zinot
{
namespace Textool
{
class ConfigDao
{
private:
   bool compressed;
   FREE_IMAGE_FILTER mipmapFilter;
   GlBindTextureDao glBindTexture;
   GlTexImageDao glTexImage;
   GlTexParameterDao glTexParameter;
   LayersNamePatternsDao layersNamePatterns;
public:
   bool loadFromJsonObject(QJsonObject const & jsonObj);

   bool isCompressed() const
   { return compressed; }

   const GlBindTextureDao & getGlBindTexture() const
   { return glBindTexture; }

   const GlTexImageDao & getGlTexImage() const
   { return glTexImage; }

   const GlTexParameterDao & getGlTexParameter() const
   { return glTexParameter; }

   const LayersNamePatternsDao & getLayersNamePatterns() const
   { return layersNamePatterns; }

   FREE_IMAGE_FILTER getMipmapFilter() const
   { return mipmapFilter; }
};
}
}

#endif //ZINOTPROJECT_CONFROOT_HPP
