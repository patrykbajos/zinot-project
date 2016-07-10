//
// Created by patryk on 09.03.16.
//

#ifndef ZINOTPROJECT_GLBINDTEXTURE_HPP
#define ZINOTPROJECT_GLBINDTEXTURE_HPP

#include <GL/gl.h>

class QJsonObject;

namespace Zinot
{
namespace Textool
{
class GlBindTexture
{
private:
   GLenum target;
public:
   bool fromJsonObject(QJsonObject const & jsonObj);

   GLenum getTarget() const
   { return target; }
};
}
}


#endif //ZINOTPROJECT_GLBINDTEXTURE_HPP
