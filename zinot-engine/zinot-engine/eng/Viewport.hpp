//
// Created by patryk on 26.10.15.
//

#ifndef ZINOTENGINE_WINDOW_HPP
#define ZINOTENGINE_WINDOW_HPP

#include <memory>
#include <gl_core_3_3.hpp>

#include <SFML/Window.hpp>
#include <QStack>
#include <glm/glm.hpp>

#include <zinot-engine/res-sys/MapResMgr.hpp>
#include <zinot-engine/eng/FPSCamera.hpp>
#include <zinot-engine/res/models/Model.hpp>
#include <zinot-engine/res/Texture.hpp>
#include <zinot-engine/res/GpuProgram.hpp>

namespace sf
{
class Event;
}

namespace Zinot
{
class Window;

class Viewport
{
protected:
   Window * parentWnd; // Is managed by Zinot::Engine
   std::unique_ptr<MapResMgr> resMgr;

   FPSCamera cam;
   GpuProgram * program; // Are managed by Zinot::MapResMgr
   Texture * texture;
   Model * model;

   GLuint vbo;
   GLuint ebo;

   typedef glm::mat4 ModelMatrixType;
   typedef glm::mat4 ViewMatrixType;
   typedef glm::mat4 ProjectionMatrixType;
   ModelMatrixType modelMatrix;
   ViewMatrixType viewMatrix;
   ProjectionMatrixType projMatrix;

   QStack<ModelMatrixType> modelMatrixStack;
public:
   void initializeScene();
   bool dispatchEvent(sf::Event & event);
   void render();

   void setParentWindow(Window * value)
   { parentWnd = value; }
};
}

#endif //ZINOTENGINE_WINDOW_HPP
