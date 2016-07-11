//
// Created by patryk on 10.05.16.
//
#include <gl_core_3_3.hpp>
#include "Window.hpp"

namespace Zinot
{
void Window::createWindow()
{
   window.reset(new sf::Window(sf::VideoMode(800, 600), "OpenGL",
                               sf::Style::Default,
                               sf::ContextSettings(24, 8, 0, 3, 3, sf::ContextSettings::Core)));

   window->setVerticalSyncEnabled(true);

   gl::sys::LoadFunctions();
}

bool Window::addViewport(Viewport * newViewport)
{
   viewport.reset(newViewport);
   return true;
}

bool Window::enterMainLoop()
{
   viewport->setParentWindow(this);
   viewport->initializeScene();

   bool running = true;
   while (running)
   {
      sf::Event event;
      while (window->pollEvent(event))
      {
         if (event.type == sf::Event::Closed)
         {
            running = false;
            break;
         }
         /*if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::BackSpace));
         {
            running = false;
         }*/
         if (event.type == sf::Event::Resized)
         {
            gl::Viewport(0, 0, event.size.width, event.size.height);
         }

         viewport->dispatchEvent(event);
      }

      viewport->render();
      window->display();
   }

   return true;
}
}

