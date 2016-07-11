#ifndef RESOURCE_HPP
#define RESOURCE_HPP

#include <zinot-engine/res-sys/MapResMgr.hpp>

namespace Zinot
{


class Resource
{
private:
   MapResMgr::ResRefCount refCount;
   MapResMgr::ResName resId;
   MapResMgr * resOwner;
public:
   Resource();
   Resource(Resource && src);
   Resource(const Resource & src);
   virtual ~Resource();

   virtual void decRefCount()
   { --refCount; }

   virtual int64_t getRefCount()
   { return refCount; }

   virtual void incRefCount()
   { ++refCount; }

   virtual QString getName()
   { return resOwner->getNamesRegister().getName(resId); }

   virtual MapResMgr::ResName getResId()
   { return resId; }

   virtual void setName(MapResMgr::ResName newName)
   { resId = newName; }

   virtual void setResOwner(MapResMgr * newResOwner)
   { resOwner = newResOwner; }

   virtual MapResMgr * getResOwner()
   { return resOwner; }
};
}

#endif // RESOURCE_HPP
