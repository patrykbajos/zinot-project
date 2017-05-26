//
// Created by patryk on 10.05.16.
//

#ifndef ZINOTENGINEPROJECT_WINDOW_HPP
#define ZINOTENGINEPROJECT_WINDOW_HPP

#include <memory>
#include <SFML/Window.hpp>

namespace Zinot
{
class Engine;

class Scene;

class Window
{
protected:
   std::unique_ptr<sf::Window> sfWindow;
   Engine * parentEnginePtr;
   Scene * scenePtr;
public:
   Window(Engine * enginePtr);

   void open();
   bool enterMainLoop();
   void close();

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
