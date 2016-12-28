//
// Created by patryk on 09.03.16.
//

#include "GlBindTextureDao.hpp"

#ifdef _WIN32
#include <GL/glext.h>
#endif

#include <QMap>

namespace Zinot
{
namespace Textool
{
bool GlBindTextureDao::loadFromJsonObject(const QJsonObject & jsonObj)
{
   static QMap<QString, GLenum> targetMap{
      {"GL_TEXTURE_1D",       GL_TEXTURE_1D},
      {"GL_TEXTURE_2D",       GL_TEXTURE_2D},
      {"GL_TEXTURE_3D",       GL_TEXTURE_3D},
      {"GL_TEXTURE_CUBE_MAP", GL_TEXTURE_CUBE_MAP}
   };

   // Default is 2D texture
   target = targetMap[jsonObj["target"].toString("GL_TEXTURE_2D")];

   return true;
}
}
}