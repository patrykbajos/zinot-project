//
// Created by patryk on 10.05.16.
//
#include <gl_core_3_3.hpp>
#include "Window.hpp"

namespace Zinot
{
Window::Window(Engine * enginePtr)
{
   parentEnginePtr = enginePtr;
}

void Window::open()
{
   sfWindow.reset(new sf::Window(sf::VideoMode(800, 600), "OpenGL",
                               sf::Style::Default,
                               sf::ContextSettings(24, 8, 0, 3, 3, sf::ContextSettings::Core)));
   sfWindow->setVerticalSyncEnabled(true);

   gl::sys::LoadFunctions();
}

bool Window::enterMainLoop()
{
   bool running = true;
   while (running)
   {
      sf::Event event;
      while (sfWindow->pollEvent(event))
      {
         if (event.type == sf::Event::Closed)
            running = false;
      }

      sfWindow->display();
   }

   return true;
}

void Window::close()
{
   sfWindow->close();
}

}

