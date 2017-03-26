//
// Created by patryk on 19.08.16.
//

#include "GameObject.hpp"

namespace Zinot
{

const QString & GameObject::getName() const
{
   return name;
}

GameObject * GameObject::getParent() const
{
   return parent;
}

const QMap<QString, std::unique_ptr<GameObject>> & GameObject::getChildren() const
{
   return children;
}

std::vector<std::unique_ptr<Component>> & GameObject::getComponents()
{
   return components;
}

void GameObject::setName(const QString & name)
{
   GameObject::name = name;
}

void GameObject::setParent(GameObject * parent)
{
   GameObject::parent = parent;
}
}