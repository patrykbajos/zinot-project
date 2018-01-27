#include <zinot-engine/eng/Engine.hpp>

#include <zinot-engine/eng/ResMgrList.hpp>
#include <zinot-utils/Logger.hpp>

namespace Zinot
{

Engine::Engine()
{
   resMgrs.resize((int) ResMgrType::Size);

   for (auto & resMgr : resMgrs) {
      resMgr.reset(new MapResMgr(this));
   }
}

int Engine::main()
{
   Logger & log = Logger::getInstance();
   log.createLog("logs/log");
   log.log("(INFO): Starting engine...");

   windowPtr.reset(new Window(this));
   scenePtr.reset(new Scene(this));

   bool sceneResult = scenePtr->loadFromJsonFile("media/scene.json");
   log.log("(STATUS): Loading scene result is: " + QString(sceneResult ? "true" : "false"));

   windowPtr->setScenePtr(scenePtr.get());
   windowPtr->open();
   windowPtr->enterMainLoop();
   windowPtr->close();

   return 0;
}
}