//
// Created by patryk on 26.10.15.
//

#ifndef ZINOT_ENGINE_HPP
#define ZINOT_ENGINE_HPP

#include <memory>
#include <zinot-engine/engine/Window.hpp>

namespace Zinot
{

class Engine
{
   std::unique_ptr<Window> mainWindow;
public:
   int main();
};
}

#endif //ZINOT_ENGINE_HPP
