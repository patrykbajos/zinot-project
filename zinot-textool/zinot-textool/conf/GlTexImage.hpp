//
// Created by patryk on 09.03.16.
//

#ifndef ZINOTPROJECT_GLTEXIMAGE_HPP
#define ZINOTPROJECT_GLTEXIMAGE_HPP

#include <GL/gl.h>

class QJsonObject;

namespace Zinot
{
namespace Textool
{
class GlTexImage
{
private:
   GLenum internalFormat;
   GLenum format;
   GLenum type;

   void parseInternalFormat(const QJsonObject & jsonObj);
   void parseFormat(const QJsonObject & jsonObj);
   void parseType(const QJsonObject & jsonObj);
public:
   bool fromJsonObject(QJsonObject const & jsonObj);

   GLenum getInternalFormat() const
   { return internalFormat; }

   GLenum getFormat() const
   { return format; }

   GLenum getType() const
   { return type; }
};
}
}


#endif //ZINOTPROJECT_GLTEXIMAGE_HPP
