//
// Created by patryk on 25.03.17.
//

#ifndef ZINOT_PROJECT_RESMGRLIST_HPP
#define ZINOT_PROJECT_RESMGRLIST_HPP

#include <memory>
#include <vector>
#include <zinot-engine/res-sys/MapResMgr.hpp>

namespace Zinot
{

typedef std::unique_ptr<MapResMgr> ResMgrPtr;
typedef std::vector<ResMgrPtr> ResMgrsContainer;

enum class ResMgrType
{
   ModelsMgr, TexturesMgr, ShadersMgr, Size
};

extern ResMgrsContainer resMgrs;
}

#endif //ZINOT_PROJECT_RESMGRLIST_HPP
