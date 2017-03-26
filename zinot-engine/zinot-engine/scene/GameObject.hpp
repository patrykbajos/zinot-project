//
// Created by patryk on 19.08.16.
//

#ifndef ZINOT_PROJECT_GAMEOBJECT_HPP
#define ZINOT_PROJECT_GAMEOBJECT_HPP

#include <memory>
#include <vector>
#include <QString>
#include <QMap>
#include <zinot-engine/scene/components/Component.hpp>

namespace Zinot
{

class GameObject
{
protected:
   QString name;
   GameObject* parent;
   QMap<QString, std::unique_ptr<GameObject>> children;
   std::vector<std::unique_ptr<Component>> components;
public:
   void setName(const QString & name);
   void setParent(GameObject * parent);
   const QString & getName() const;
   GameObject * getParent() const;
   const QMap<QString, std::unique_ptr<GameObject>> & getChildren() const;
   std::vector<std::unique_ptr<Component>> & getComponents();
};

}

#endif //ZINOT_PROJECT_GAMEOBJECT_HPP
