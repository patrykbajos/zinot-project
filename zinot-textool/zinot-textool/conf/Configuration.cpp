//
// Created by patryk on 09.03.16.
//

#include "Configuration.hpp"

#include <QJsonObject>
#include <QMap>

namespace Zinot
{
namespace Textool
{
bool Configuration::fromJsonObject(QJsonObject const & jsonObj)
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

   glTexImage.fromJsonObject(jsonObj.value("glTexImage").toObject());
   glBindTexture.fromJsonObject(jsonObj["glBindTexture"].toObject());
   glTexParameter.fromJsonObject(jsonObj["glTexParameter"].toObject());
   layersNamePatterns.fromJsonObject(jsonObj["layersNamePatterns"].toObject());

   return false;
}
}
}