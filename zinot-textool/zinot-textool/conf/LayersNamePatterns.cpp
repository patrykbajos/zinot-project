//
// Created by patryk on 12.03.16.
//

#include "LayersNamePatterns.hpp"

#include <QJsonObject>

namespace Zinot
{
namespace Textool
{
bool LayersNamePatterns::fromJsonObject(QJsonObject const & jsonObj)
{
   positiveXEnd = jsonObj["positiveXEnd"].toString("-px");
   negativeXEnd = jsonObj["negativeXEnd"].toString("-nx");

   positiveYEnd = jsonObj["positiveYEnd"].toString("-py");
   negativeYEnd = jsonObj["negativeYEnd"].toString("-ny");

   positiveZEnd = jsonObj["positiveZEnd"].toString("-pz");
   negativeZEnd = jsonObj["negativeZEnd"].toString("-nz");

   texDepthSeparator = jsonObj["texDepthSeparator"].toString("-");

   return true;
}
}
}