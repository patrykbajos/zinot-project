//
// Created by patryk on 09.03.16.
//

#include "ConfigDao.hpp"

#include <QJsonObject>
#include <QMap>

namespace Zinot
{
namespace Textool
{
bool ConfigDao::loadFromJsonObject(QJsonObject const & jsonObj)
{
   compressed = jsonObj["compressed"].toBool(true);

   QMap<QString, FREE_IMAGE_FILTER> mipmapFilterMap = {
      {"bicubic",    FILTER_BICUBIC},
      {"bilinear",   FILTER_BILINEAR},
      {"box",        FILTER_BOX},
      {"bspline",    FILTER_BSPLINE},
      {"catmullrom", FILTER_CATMULLROM},
      {"lanczos3",   FILTER_LANCZOS3}
   };

   mipmapFilter = mipmapFilterMap[jsonObj["mipmapFilter"].toString("bicubic")];

   glTexImage.loadFromJsonObject(jsonObj.value("glTexImage").toObject());
   glBindTexture.loadFromJsonObject(jsonObj["glBindTexture"].toObject());
   glTexParameter.loadFromJsonObject(jsonObj["glTexParameter"].toObject());
   layersNamePatterns.loadFromJsonObject(jsonObj["layersNamePatterns"].toObject());

   return false;
}
}
}