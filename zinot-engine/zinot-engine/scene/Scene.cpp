//
// Created by patryk on 30.08.16.
//
#include "Scene.hpp"

#include <zinot-engine/scene/components/Transform.hpp>
#include <zinot-engine/res/models/Model.hpp>
#include <zinot-engine/eng/ResMgrList.hpp>
#include <zinot-engine/scene/components/ModelRenderer.hpp>

namespace Zinot
{

bool Scene::loadFromJsonFile(const QString & filePath)
{
   rootGameObject.reset(new GameObject());

   rootGameObject->setName("table");
   rootGameObject->setParent(nullptr);
   auto & c = rootGameObject->getComponents();

   std::unique_ptr<Component> transform(new Transform(glm::vec3(0.0f, 0.0f, -2.0f),
                                                      glm::vec3(0.0f, 0.0f, 0.0f),
                                                      glm::vec3(0.0f, 0.0f, 0.0f)));

   ResMgrPtr & resMgrPtr = resMgrs.at((int) ResMgrType::ModelsMgr);
   MapResMgr::ResPtr<Model> mdl = resMgrPtr->getRes<Model>("media/models/table/table.json");
   mdl->loadFromFile();

   std::unique_ptr<Component> mr(new ModelRenderer(mdl));

   c.push_back(std::move(transform));
   c.push_back(std::move(mr));

   return true;
}

}