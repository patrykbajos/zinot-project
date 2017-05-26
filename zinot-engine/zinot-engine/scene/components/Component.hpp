//
// Created by patryk on 12.01.17.
//

#ifndef ZINOT_PROJECT_COMPONENT_HPP
#define ZINOT_PROJECT_COMPONENT_HPP

namespace Zinot
{

class Component
{
public:
   enum class Type
   {
      None, Transform, ModelRenderer
   };
protected:
   Type componentType;

   void setComponentType(Type type)
   { componentType = type; };
public:
   Component() : componentType(Type::None)
   {
   };

   virtual ~Component()
   {
   };

   virtual Type getComponentType() const
   {
      return componentType;
   };
};
}

#endif //ZINOT_PROJECT_COMPONENT_HPP
