//
// Created by patryk on 28.03.17.
//

#ifndef ZINOT_PROJECT_MODELRENDERER_HPP
#define ZINOT_PROJECT_MODELRENDERER_HPP

#include <zinot-engine/scene/components/Component.hpp>
#include <zinot-engine/res/models/Model.hpp>
#include <zinot-engine/res-sys/MapResMgr.hpp>

namespace Zinot
{

class ModelRenderer : public Component
{
private:
   MapResMgr::ResPtr<Model> model;
public:
   ModelRenderer() : Component() {
      setComponentType(Type::ModelRenderer);
   }

   ModelRenderer(MapResMgr::ResPtr<Model> model) : Component(), ModelRenderer(){
      ModelRenderer::model = model;
   }

   virtual ~ModelRenderer() override {
      MapResMgr * mgr = model->getResOwner();
      QString name = model->getName();
      model.reset();
      mgr->tryDeleteRes(name);
   }

   const MapResMgr::ResPtr<Model> & getModel() const {
      return model;
   }
   void setModel(const MapResMgr::ResPtr<Model> & model) {
      ModelRenderer::model = model;
   }
};

}

#endif //ZINOT_PROJECT_MODELRENDERER_HPP
