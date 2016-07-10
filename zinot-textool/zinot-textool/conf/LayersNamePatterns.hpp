//
// Created by patryk on 12.03.16.
//

#ifndef ZINOTPROJECT_LAYERSNAMEPATTERNS_HPP
#define ZINOTPROJECT_LAYERSNAMEPATTERNS_HPP

#include <QString>

class QJsonObject;

namespace Zinot
{
namespace Textool
{
class LayersNamePatterns
{
private:
   QString positiveXEnd;
   QString negativeXEnd;

   QString positiveYEnd;
   QString negativeYEnd;

   QString positiveZEnd;
   QString negativeZEnd;

   QString texDepthSeparator;
public:
   bool fromJsonObject(QJsonObject const & jsonObj);

   const QString & getPositiveXEnd() const
   { return positiveXEnd; }

   const QString & getNegativeXEnd() const
   { return negativeXEnd; }

   const QString & getPositiveYEnd() const
   { return positiveYEnd; }

   const QString & getNegativeYEnd() const
   { return negativeYEnd; }

   const QString & getPositiveZEnd() const
   { return positiveZEnd; }

   const QString & getNegativeZEnd() const
   { return negativeZEnd; }

   const QString & getTexDepthSeparator() const
   { return texDepthSeparator; }
};
}
}


#endif //ZINOTPROJECT_LAYERSNAMEPATTERNS_HPP
