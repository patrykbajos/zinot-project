//
// Created by patryk on 30.08.16.
//

#ifndef ZINOT_PROJECT_SCENE_HPP
#define ZINOT_PROJECT_SCENE_HPP

#include <QVector>
#include <memory>
#include <zinot-engine/scene/GameObject.hpp>

namespace Zinot
{

class Engine;

class Scene
{
private:
   Engine * engine;

   QVector<QString> lightingModelList;
   std::unique_ptr<GameObject> rootGameObject;
public:
    explicit Scene(Engine *engine) : engine(engine), lightingModelList({"Albedo", "Phong", "PBR"})/* TODO: Load lighting mdls */ {}

    bool loadFromJsonFile(const QString & filePath);

   const QVector<QString> & getLightingModelList() const
   {
      return lightingModelList;
   }
};

}

#endif //ZINOT_PROJECT_SCENE_HPP
