//
// Created by patryk on 25.04.16.
//

#ifndef ZINOTENGINEPROJECT_TEXTURE_HPP
#define ZINOTENGINEPROJECT_TEXTURE_HPP

#include <GL/gl.h>

#include <zinot-engine/resources/Resource.hpp>

namespace Zinot
{
class Texture : public Resource
{
protected:
   GLuint id;
public:
   virtual ~Texture();
   bool loadFromFile();

   GLuint getId() const
   {
      return id;
   }
};
}


#endif //ZINOTENGINEPROJECT_TEXTURE_HPP
