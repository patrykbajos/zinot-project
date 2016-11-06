//
// Created by patryk on 26.10.15.
//

#ifndef ZINOT_ENGINE_HPP
#define ZINOT_ENGINE_HPP

#include <memory>
#include <zinot-engine/eng/Window.hpp>
#include <zinot-engine/scene/dao/SceneDao.hpp>

namespace Zinot
{
class Engine
{
   std::unique_ptr<Window> mainWindow;
   std::unique_ptr<SceneDao> mainScene;
public:
   int main();
};
}

#endif //ZINOT_ENGINE_HPP
