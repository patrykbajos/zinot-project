#include <zinot-engine/eng/Engine.hpp>

#include <zinot-utils/Logger.hpp>
#include <zinot-engine/eng/Window.hpp>

namespace Zinot
{
int Engine::main()
{
   Logger & log = Logger::getInstance();
   log.createLog("logs/log");
   log.log("(INFO) Starting engine...");

   mainWindow.reset(new Window(this));
   mainScene.reset(new SceneDao());
   mainScene->loadFromJSON("media/scene.json");

   mainWindow->setScenePtr(mainScene.get());
   mainWindow->open();
   mainWindow->enterMainLoop();
   mainWindow->close();

   return 0;
}
}