//
// Created by patryk on 12.03.16.
//

#include "GlTexParameterDao.hpp"

#include <GL/glext.h>
#include <QJsonObject>
#include <QMap>

namespace Zinot
{
namespace Textool
{
bool GlTexParameterDao::loadFromJsonObject(const QJsonObject & jsonObj)
{
   parseMinFilter(jsonObj);
   parseMagFilter(jsonObj);
   parseWrapping(jsonObj);

   glTextureLodBias = jsonObj["GL_TEXTURE_LOD_BIAS"].toInt();
   glTextureMinLod = jsonObj["GL_TEXTURE_MIN_LOD"].toInt(-1000);
   glTextureMaxLod = jsonObj["GL_TEXTURE_MAX_LOD"].toInt(1000);
   glTextureMaxLevel = jsonObj["GL_TEXTURE_MAX_LEVEL"].toInt(1000);

   return true;
}

void GlTexParameterDao::parseWrapping(const QJsonObject & jsonObj)
{
   static QMap<QString, GLenum> wrapMap{
      {"GL_CLAMP",           GL_CLAMP},
      {"GL_CLAMP_TO_BORDER", GL_CLAMP_TO_BORDER},
      {"GL_CLAMP_TO_EDGE",   GL_CLAMP_TO_EDGE},
      {"GL_MIRRORED_REPEAT", GL_MIRRORED_REPEAT},
      {"GL_REPEAT",          GL_REPEAT}
   };

   glTextureWrapS = wrapMap[jsonObj["GL_TEXTURE_WRAP_S"].toString("GL_REPEAT")];
   glTextureWrapT = wrapMap[jsonObj["GL_TEXTURE_WRAP_T"].toString("GL_REPEAT")];
   glTextureWrapR = wrapMap[jsonObj["GL_TEXTURE_WRAP_R"].toString("GL_REPEAT")];
}

void GlTexParameterDao::parseMagFilter(const QJsonObject & jsonObj)
{
   static QMap<QString, GLenum> magFilterMap{
      {"GL_NEAREST", GL_NEAREST},
      {"GL_LINEAR",  GL_LINEAR},
   };

   glTextureMagFilter = magFilterMap[jsonObj["GL_TEXTURE_MAG_FILTER"].toString("GL_LINEAR")];
}

void GlTexParameterDao::parseMinFilter(const QJsonObject & jsonObj)
{
   static QMap<QString, GLenum> minFilterMap{
      {"GL_NEAREST",               GL_NEAREST},
      {"GL_LINEAR",                GL_LINEAR},
      {"GL_LINEAR_MIPMAP_NEAREST", GL_LINEAR_MIPMAP_NEAREST},
      {"GL_NEAREST_MIPMAP_LINEAR", GL_NEAREST_MIPMAP_LINEAR},
      {"GL_LINEAR_MIPMAP_LINEAR",  GL_LINEAR_MIPMAP_LINEAR}
   };

   glTextureMinFilter = minFilterMap[
      jsonObj["GL_TEXTURE_MIN_FILTER"].toString("GL_LINEAR_MIPMAP_LINEAR")
   ];
}
}
}