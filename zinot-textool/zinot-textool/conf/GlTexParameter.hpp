//
// Created by patryk on 12.03.16.
//

#ifndef ZINOTPROJECT_GLTEXPARAMETER_HPP
#define ZINOTPROJECT_GLTEXPARAMETER_HPP

#include <GL/gl.h>

class QJsonObject;


namespace Zinot
{
namespace Textool
{
class GlTexParameter
{
public:
   bool fromJsonObject(const QJsonObject & jsonObj);
private:
   void parseMinFilter(const QJsonObject & jsonObj);

   void parseMagFilter(const QJsonObject & jsonObj);

   void parseWrapping(const QJsonObject & jsonObj);

   GLint glTextureLodBias;
   GLenum glTextureMinFilter;
   GLenum glTextureMagFilter;
   GLint glTextureMinLod;
   GLint glTextureMaxLod;
   GLint glTextureMaxLevel;
   GLenum glTextureWrapS;
   GLenum glTextureWrapT;
   GLenum glTextureWrapR;
};
}
}

#endif //ZINOTPROJECT_GLTEXPARAMETER_HPP
