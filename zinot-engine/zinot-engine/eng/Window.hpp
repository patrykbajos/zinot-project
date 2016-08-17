//
// Created by patryk on 10.05.16.
//

#ifndef ZINOTENGINEPROJECT_WINDOW_HPP
#define ZINOTENGINEPROJECT_WINDOW_HPP

#include <memory>
#include <SFML/Window.hpp>
#include <zinot-engine/scene/Scene.hpp>

namespace Zinot
{
class Engine;

class Window
{
protected:
   std::unique_ptr<sf::Window> sfWindow;
   Engine * parentEnginePtr;
   Scene * scenePtr;
public:
   void open();
   bool enterMainLoop();
   void close();

   Window(Engine * enginePtr);

   const sf::Window * getSfWindow() const
   {
      return sfWindow.get();
   }

   void setScenePtr(Scene * scenePtr)
   {
      Window::scenePtr = scenePtr;
   }
};
}

#endif //ZINOTENGINEPROJECT_WINDOW_HPP
