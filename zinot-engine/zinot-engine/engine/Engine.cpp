#include <zinot-engine/engine/Engine.hpp>

#include <zinot-utils/Logger.hpp>
#include <zinot-engine/engine/Viewport.hpp>
#include <zinot-engine/engine/Window.hpp>

namespace Zinot
{
int Engine::main()
{
   Logger & log = Logger::getInstance();
   log.createLog("logs/");
   log.log("Starting engine...");

   mainWindow.reset(new Window());
   mainWindow->setParentEngine(this);
   mainWindow->addViewport(new Viewport);

   mainWindow->createWindow();
   mainWindow->enterMainLoop();

   return 0;
}
}