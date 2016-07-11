//
// Created by patryk on 10.05.16.
//

#ifndef ZINOTENGINEPROJECT_WINDOW_HPP
#define ZINOTENGINEPROJECT_WINDOW_HPP

#include <memory>

#include <SFML/Window.hpp>
#include <zinot-engine/eng/Viewport.hpp>

namespace Zinot
{
class Engine;

class Window
{
protected:
   std::unique_ptr<sf::Window> window;
   std::unique_ptr<Viewport> viewport;
   Engine * parentEngine;

public:
   void createWindow();
   bool addViewport(Viewport * newViewport);
   bool enterMainLoop();

   const sf::Window * getSFMLWindow() const
   {
      return window.get();
   }

   void setParentEngine(Engine * value)
   {
      parentEngine = value;
   }
};
}

#endif //ZINOTENGINEPROJECT_WINDOW_HPP
