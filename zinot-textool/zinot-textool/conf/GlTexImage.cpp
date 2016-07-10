//
// Created by patryk on 09.03.16.
//
#include <gl_core_3_3.hpp>
#include "GlTexImage.hpp"

#include <QJsonObject>
#include <QMap>

namespace Zinot
{
namespace Textool
{
bool GlTexImage::fromJsonObject(const QJsonObject & jsonObj)
{
   // For compressed, default as DXT1 RGB w/o aplha
   parseInternalFormat(jsonObj);

   // For uncompressed, no default value
   parseFormat(jsonObj);
   parseType(jsonObj);

   return true;
}

void GlTexImage::parseType(const QJsonObject & jsonObj)
{
   static QMap<QString, GLenum> typeMap{
      {"GL_UNSIGNED_BYTE",               gl::UNSIGNED_BYTE},
      {"GL_BYTE",                        gl::BYTE},
      {"GL_UNSIGNED_SHORT",              gl::UNSIGNED_SHORT},
      {"GL_SHORT",                       gl::SHORT},
      {"GL_UNSIGNED_INT",                gl::UNSIGNED_INT},
      {"GL_INT",                         gl::INT},
      {"GL_FLOAT",                       gl::FLOAT},
      {"GL_UNSIGNED_BYTE_3_3_2",         gl::UNSIGNED_BYTE_3_3_2},
      {"GL_UNSIGNED_BYTE_2_3_3_REV",     gl::UNSIGNED_BYTE_2_3_3_REV},
      {"GL_UNSIGNED_SHORT_5_6_5",        gl::UNSIGNED_SHORT_5_6_5},
      {"GL_UNSIGNED_SHORT_5_6_5_REV",    gl::UNSIGNED_SHORT_5_6_5_REV},
      {"GL_UNSIGNED_SHORT_4_4_4_4",      gl::UNSIGNED_SHORT_4_4_4_4},
      {"GL_UNSIGNED_SHORT_4_4_4_4_REV",  gl::UNSIGNED_SHORT_4_4_4_4_REV},
      {"GL_UNSIGNED_SHORT_5_5_5_1",      gl::UNSIGNED_SHORT_5_5_5_1},
      {"GL_UNSIGNED_SHORT_1_5_5_5_REV",  gl::UNSIGNED_SHORT_1_5_5_5_REV},
      {"GL_UNSIGNED_INT_8_8_8_8",        gl::UNSIGNED_INT_8_8_8_8},
      {"GL_UNSIGNED_INT_8_8_8_8_REV",    gl::UNSIGNED_INT_8_8_8_8_REV},
      {"GL_UNSIGNED_INT_10_10_10_2",     gl::UNSIGNED_INT_10_10_10_2},
      {"GL_UNSIGNED_INT_2_10_10_10_REV", gl::UNSIGNED_INT_2_10_10_10_REV}
   };

   type = typeMap[jsonObj["type"].toString()];
}

void GlTexImage::parseFormat(const QJsonObject & jsonObj)
{
   static QMap<QString, GLenum> formatMap{
      {"GL_DEPTH_COMPONENT", gl::DEPTH_COMPONENT},
      {"GL_STENCIL_INDEX",   gl::STENCIL_INDEX},
      {"GL_DEPTH_STENCIL",   gl::DEPTH_STENCIL},
      {"GL_RED",             gl::RED},
      {"GL_GREEN",           gl::GREEN},
      {"GL_BLUE",            gl::BLUE},
      {"GL_RG",              gl::RG},
      {"GL_RGB",             gl::RGB},
      {"GL_BGR",             gl::BGR},
      {"GL_RGBA",            gl::RGBA},
      {"GL_BGRA",            gl::BGRA},
      {"GL_RED_INTEGER",     gl::RED_INTEGER},
      {"GL_GREEN_INTEGER",   gl::GREEN_INTEGER},
      {"GL_BLUE_INTEGER",    gl::BLUE_INTEGER},
      {"GL_RG_INTEGER",      gl::RG_INTEGER},
      {"GL_RGB_INTEGER",     gl::RGB_INTEGER},
      {"GL_BGR_INTEGER",     gl::BGR_INTEGER},
      {"GL_RGBA_INTEGER",    gl::RGBA_INTEGER},
      {"GL_BGRA_INTEGER",    gl::BGRA_INTEGER}
   };

   format = formatMap[jsonObj["format"].toString()];
}

void GlTexImage::parseInternalFormat(const QJsonObject & jsonObj)
{
   static QMap<QString, GLenum> internalFormatMap{
      {"GL_COMPRESSED_RGB_S3TC_DXT1_EXT",  gl::COMPRESSED_RGB_S3TC_DXT1_EXT},
      {"GL_COMPRESSED_RGBA_S3TC_DXT1_EXT", gl::COMPRESSED_RGBA_S3TC_DXT1_EXT},
      {"GL_COMPRESSED_RGBA_S3TC_DXT3_EXT", gl::COMPRESSED_RGBA_S3TC_DXT3_EXT},
      {"GL_COMPRESSED_RGBA_S3TC_DXT5_EXT", gl::COMPRESSED_RGBA_S3TC_DXT5_EXT}
   };

   const QJsonValue & value = jsonObj.value("internalFormat");
   const QString & key = value.toString("GL_COMPRESSED_RGBA_S3TC_DXT1_EXT");
   internalFormat = internalFormatMap[key];
}
}
}