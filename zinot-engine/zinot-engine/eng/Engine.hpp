//
// Created by patryk on 26.10.15.
//

#ifndef ZINOT_ENGINE_HPP
#define ZINOT_ENGINE_HPP

#include <memory>
#include <zinot-engine/eng/Window.hpp>
#include <zinot-engine/scene/Scene.hpp>

namespace Zinot
{

/**
 * @brief The main class of Zinot Engine.
 * Main class of engine. Is called from main() and enters main loop.
 */
class Engine
{
private:
   std::unique_ptr<Window> windowPtr; /// Main Window pointer. Engine is owner of main window. The window is created after call to main() method.
   std::unique_ptr<Scene> scenePtr;   /// Main Scene pointer. Engne is owner of main scene. The scene is default displayed in Main Window.
public:
   /**
    * Performs intializtion of engine.
    */
   Engine();

   /**
    * Main engine method. It creates and opens window, enters main loop and performs cleaning at closing engine.
    * Called by main() function after creating engine. Return value is passed to exit point.
    * @return Engine return value. Passed to exit point by main() function.
    */
   int main();

   const std::unique_ptr<Window> & getWindowPtr() const
   {
      return windowPtr;
   }

   const std::unique_ptr<Scene> & getScenePtr() const
   {
      return scenePtr;
   }
};
}

#endif //ZINOT_ENGINE_HPP
