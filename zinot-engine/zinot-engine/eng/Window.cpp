#include <gl_core_3_3.hpp>
#include "Window.hpp"

namespace Zinot
{
Window::Window(Engine * parentEnginePtr)
{
   Window::engine = parentEnginePtr;
}

void Window::open()
{
   sfWindow = std::make_unique<sf::Window>(
      sf::VideoMode(800, 600), "OpenGL",
      sf::Style::Default,
      sf::ContextSettings(24, 8, 0, 3, 3, sf::ContextSettings::Core)
   );
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

      gl::Clear(gl::COLOR_BUFFER_BIT);
      gl::ClearColor(0.0f, 0.0f, 0.0f, 1.0f);

      sfWindow->display();
   }

   return true;
}

void Window::close()
{
   sfWindow->close();
}

}

