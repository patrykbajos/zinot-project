//
// Created by patryk on 09.03.16.
//
#include "GlTexImageDao.hpp"

#include <GL/glext.h>
#include <QJsonObject>
#include <QMap>

namespace Zinot
{
namespace Textool
{
bool GlTexImageDao::loadFromJsonObject(const QJsonObject & jsonObj)
{
   // For compressed, default as DXT1 RGB w/o aplha
   parseInternalFormat(jsonObj);

   // For uncompressed, no default value
   parseFormat(jsonObj);
   parseType(jsonObj);

   return true;
}

void GlTexImageDao::parseType(const QJsonObject & jsonObj)
{
   static QMap<QString, GLenum> typeMap{
      {"GL_UNSIGNED_BYTE",               GL_UNSIGNED_BYTE},
      {"GL_BYTE",                        GL_BYTE},
      {"GL_UNSIGNED_SHORT",              GL_UNSIGNED_SHORT},
      {"GL_SHORT",                       GL_SHORT},
      {"GL_UNSIGNED_INT",                GL_UNSIGNED_INT},
      {"GL_INT",                         GL_INT},
      {"GL_FLOAT",                       GL_FLOAT},
      {"GL_UNSIGNED_BYTE_3_3_2",         GL_UNSIGNED_BYTE_3_3_2},
      {"GL_UNSIGNED_BYTE_2_3_3_REV",     GL_UNSIGNED_BYTE_2_3_3_REV},
      {"GL_UNSIGNED_SHORT_5_6_5",        GL_UNSIGNED_SHORT_5_6_5},
      {"GL_UNSIGNED_SHORT_5_6_5_REV",    GL_UNSIGNED_SHORT_5_6_5_REV},
      {"GL_UNSIGNED_SHORT_4_4_4_4",      GL_UNSIGNED_SHORT_4_4_4_4},
      {"GL_UNSIGNED_SHORT_4_4_4_4_REV",  GL_UNSIGNED_SHORT_4_4_4_4_REV},
      {"GL_UNSIGNED_SHORT_5_5_5_1",      GL_UNSIGNED_SHORT_5_5_5_1},
      {"GL_UNSIGNED_SHORT_1_5_5_5_REV",  GL_UNSIGNED_SHORT_1_5_5_5_REV},
      {"GL_UNSIGNED_INT_8_8_8_8",        GL_UNSIGNED_INT_8_8_8_8},
      {"GL_UNSIGNED_INT_8_8_8_8_REV",    GL_UNSIGNED_INT_8_8_8_8_REV},
      {"GL_UNSIGNED_INT_10_10_10_2",     GL_UNSIGNED_INT_10_10_10_2},
      {"GL_UNSIGNED_INT_2_10_10_10_REV", GL_UNSIGNED_INT_2_10_10_10_REV}
   };

   type = typeMap[jsonObj["type"].toString()];
}

void GlTexImageDao::parseFormat(const QJsonObject & jsonObj)
{
   static QMap<QString, GLenum> formatMap{
      {"GL_DEPTH_COMPONENT", GL_DEPTH_COMPONENT},
      {"GL_STENCIL_INDEX",   GL_STENCIL_INDEX},
      {"GL_DEPTH_STENCIL",   GL_DEPTH_STENCIL},
      {"GL_RED",             GL_RED},
      {"GL_GREEN",           GL_GREEN},
      {"GL_BLUE",            GL_BLUE},
      {"GL_RG",              GL_RG},
      {"GL_RGB",             GL_RGB},
      {"GL_BGR",             GL_BGR},
      {"GL_RGBA",            GL_RGBA},
      {"GL_BGRA",            GL_BGRA},
      {"GL_RED_INTEGER",     GL_RED_INTEGER},
      {"GL_GREEN_INTEGER",   GL_GREEN_INTEGER},
      {"GL_BLUE_INTEGER",    GL_BLUE_INTEGER},
      {"GL_RG_INTEGER",      GL_RG_INTEGER},
      {"GL_RGB_INTEGER",     GL_RGB_INTEGER},
      {"GL_BGR_INTEGER",     GL_BGR_INTEGER},
      {"GL_RGBA_INTEGER",    GL_RGBA_INTEGER},
      {"GL_BGRA_INTEGER",    GL_BGRA_INTEGER}
   };

   format = formatMap[jsonObj["format"].toString()];
}

void GlTexImageDao::parseInternalFormat(const QJsonObject & jsonObj)
{
   static QMap<QString, GLenum> internalFormatMap{
      {"GL_COMPRESSED_RGB_S3TC_DXT1_EXT",  GL_COMPRESSED_RGB_S3TC_DXT1_EXT},
      {"GL_COMPRESSED_RGBA_S3TC_DXT1_EXT", GL_COMPRESSED_RGBA_S3TC_DXT1_EXT},
      {"GL_COMPRESSED_RGBA_S3TC_DXT3_EXT", GL_COMPRESSED_RGBA_S3TC_DXT3_EXT},
      {"GL_COMPRESSED_RGBA_S3TC_DXT5_EXT", GL_COMPRESSED_RGBA_S3TC_DXT5_EXT}
   };

   const QJsonValue & value = jsonObj.value("internalFormat");
   const QString & key = value.toString("GL_COMPRESSED_RGBA_S3TC_DXT1_EXT");
   internalFormat = internalFormatMap[key];
}
}
}