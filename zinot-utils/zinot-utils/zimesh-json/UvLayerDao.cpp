// Created by patryk on 06.11.16.
//

#include "UvLayerDao.hpp"

#include <QJsonObject>
#include <QJsonArray>

namespace Zimesh
{
namespace UvLayerKeys
{

static const QString uvKey = "uv";
static const QString tanKey = "tan";
}

bool UvLayerDao::loadFromJsonValue(const QString & uvLayerName, const QJsonValue & jsonVal)
{
   if (!jsonVal.isObject())
      return false;
   QJsonObject jsonObj = jsonVal.toObject();

   name = uvLayerName;

   if (jsonObj.contains(UvLayerKeys::uvKey))
   {
      QJsonValue uvVal = jsonObj[UvLayerKeys::uvKey];

      if (uvVal.isArray())
      {
         QJsonArray uvArr = uvVal.toArray();

         uv.reserve(uvArr.size());
         for (QJsonValue uvCompVal : uvArr)
         {
            float uvCompFloat = (float) uvCompVal.toDouble();
            uv.append(uvCompFloat);
         }
         uv.squeeze();
      }
   }

   // Load Tangents if contains
   if (jsonObj.contains(UvLayerKeys::tanKey))
   {
      QJsonValue tanVal = jsonObj[UvLayerKeys::tanKey];

      if (tanVal.isArray())
      {
         QJsonArray tanArr = tanVal.toArray();

         tan.reserve(tanArr.size());
         for (QJsonValue tanCompVal : tanArr)
         {
            float tanCompFloat = (float) tanCompVal.toDouble();
            tan.append(tanCompFloat);
         }
         tan.squeeze();
      }
   }

   return true;
}
}