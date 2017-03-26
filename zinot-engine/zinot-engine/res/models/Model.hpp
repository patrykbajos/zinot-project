//
// Created by patryk on 14.05.16.
//

#ifndef ZINOTENGINEPROJECT_MODEL_HPP
#define ZINOTENGINEPROJECT_MODEL_HPP

#include <GL/gl.h>
#include <zinot-engine/res-sys/Resource.hpp>

namespace Zinot
{

class Model : public Resource
{
public:
   virtual ~Model() override;
   bool loadFromFile();
};

}

#endif //ZINOTENGINEPROJECT_MODEL_HPP
