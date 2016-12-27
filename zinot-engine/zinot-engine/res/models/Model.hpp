//
// Created by patryk on 14.05.16.
//

#ifndef ZINOTENGINEPROJECT_MODEL_HPP
#define ZINOTENGINEPROJECT_MODEL_HPP

#include <GL/gl.h>

#include <zinot-engine/res-sys/Resource.hpp>
#include <zinot-engine/res/Texture.hpp>

namespace Zinot
{

class Model : public Resource
{
public:
   ~Model();
   bool loadFromFile(MapResMgr * texResMgr);
};

}

#endif //ZINOTENGINEPROJECT_MODEL_HPP
