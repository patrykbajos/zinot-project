//
// Created by patryk on 25.03.17.
//

#include "ResMgrList.hpp"

namespace Zinot
{

ResMgrsContainer resMgrs;

MapResMgr * getResMgrOfType(ResMgrType resMgrType)
{
   return resMgrs[static_cast<ResMgrsContainer::size_type>(resMgrType)].get();
}

}