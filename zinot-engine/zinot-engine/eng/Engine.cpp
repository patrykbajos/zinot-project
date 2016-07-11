#include <zinot-engine/eng/Engine.hpp>

#include <zinot-utils/Logger.hpp>
#include <zinot-engine/eng/Viewport.hpp>
#include <zinot-engine/eng/Window.hpp>

namespace Zinot
{
int Engine::main()
{
   Logger & log = Logger::getInstance();
   log.createLog("logs/log");
   log.log("(INFO) Starting engine...");

   mainWindow.reset(new Window());
   mainWindow->setParentEngine(this);
   mainWindow->addViewport(new Viewport);

   mainWindow->createWindow();
   mainWindow->enterMainLoop();

   return 0;
}
}