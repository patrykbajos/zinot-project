//
// Created by patryk on 05.08.16.
//

#include "MapResMgr.hpp"

namespace Zinot
{

MapResMgr::~MapResMgr()
{
   for (Resource * res : content)
   {
      delete res;
   }
}

void MapResMgr::deleteRes(Resource::ResId resId)
{
   ContentContainer::iterator it = content.find(resId);

   if (it == content.end())
      return;

   // Dekrementuje referencje
   Resource * res = it.value();
   res->decRefCount();

   if (res->getRefCount() < 1)
   {
      delete res;
      content.erase(it);
   }
}
}
