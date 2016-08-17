#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <QMap>
#include <zinot-engine/res-sys/NamesRegister.hpp>
#include <zinot-engine/res-sys/Resource.hpp>

namespace Zinot
{

class MapResMgr
{
protected:
   typedef QMap<Resource::ResId, Resource *> ContentContainer;
   ContentContainer content;

   NamesRegister namesRegister;
public:
   ~MapResMgr();

   template<typename ResType>
   ResType * newRes(Resource::ResId name)
   {
      ContentContainer::iterator resIt = content.find(name);

      // If resource exists
      if (resIt != content.end())
      {
         resIt.value()->incRefCount();
         return (ResType *) resIt.value();
      }

      // Else, put new resource
      Resource * newRes = new ResType;
      content.insert(name, newRes);
      newRes->setResOwner(this);
      newRes->setResId(name);
      newRes->incRefCount();

      return (ResType *) newRes;
   }

   void deleteRes(Resource::ResId resId);
   NamesRegister & getNamesRegister()
   {
      return namesRegister;
   }
};
}

#endif // RESOURCEMANAGER_HPP
