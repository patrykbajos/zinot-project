#include "MapResMgr.hpp"
#include <zinot-engine/res-sys/Resource.hpp>

namespace Zinot
{
MapResMgr::~MapResMgr()
{
   for (ContentContainer::iterator it = content.begin(); it != content.end(); ++it)
   {
      Resource * res = it.value();
      if (res)
         delete res;
   }
}

Resource * MapResMgr::getRes(ResName name)
{
   ContentContainer::iterator it = content.find(name);

   if (it == content.end())
      return nullptr;

   Resource * res = it.value();
   if (res)
      res->incRefCount();

   return res;
}

Resource * MapResMgr::newRes(ResName name, Resource * newRes, bool autoDestroy)
{
   ContentContainer::iterator resIt = content.find(name);

   // If resource exists
   if (resIt != content.end())
   {
      if (autoDestroy)
         delete newRes;

      return nullptr;
   }

   // Else, put new resource
   content.insert(name, newRes);
   newRes->setResOwner(this);
   newRes->setName(name);
   newRes->incRefCount();

   return newRes;
}

void MapResMgr::deleteRes(ResName nameId)
{
   ContentContainer::iterator it = content.find(nameId);

   if (it == content.end())
      return;

   // Dekrementuje referencje
   Resource * res = it.value();
   res->decRefCount();

   if (res->getRefCount() == 0)
   {
      delete res;
      content.erase(it);
   }
}
}