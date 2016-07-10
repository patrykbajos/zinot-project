//
// Created by patryk on 27.05.16.
//

#ifndef ZINOTENGINEPROJECT_MODELNODE_HPP
#define ZINOTENGINEPROJECT_MODELNODE_HPP

#include <glm/glm.hpp>

namespace Zinot
{
struct ModelNode
{
protected:
   ModelNode * parentPtr;

   uint16_t nameLength;
   const char * name;
   glm::mat4 transformation;

   uint16_t childrenNum;
   ModelNode ** childrenPtrArray;
};
}

#endif //ZINOTENGINEPROJECT_MODELNODE_HPP
