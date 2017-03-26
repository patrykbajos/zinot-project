#include <zinot-engine/eng/Engine.hpp>

#include <zinot-engine/eng/ResMgrList.hpp>
#include <zinot-utils/Logger.hpp>

namespace Zinot
{

Engine::Engine()
{
   resMgrs.resize((int) ResMgrType::Size);

   for (auto & resMgr : resMgrs)
      resMgr.reset(new MapResMgr());
}

int Engine::main()
{
   Logger & log = Logger::getInstance();
   log.createLog("logs/log");
   log.log("(INFO): Starting engine...");

   mainWindow.reset(new Window(this));
   mainScene.reset(new Scene());
   bool sceneResult = mainScene->loadFromJsonFile("media/scene.json");
   log.log("(STATUS): Loading scene result is: " + QString(sceneResult ? "true" : "false"));

   mainWindow->setScenePtr(mainScene.get());
   mainWindow->open();
   mainWindow->enterMainLoop();
   mainWindow->close();

   return 0;
}
}