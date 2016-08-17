#ifndef RESOURCE_HPP
#define RESOURCE_HPP

#include <cstdint>
#include <QString>

namespace Zinot
{
class MapResMgr;

class Resource
{
public:
   typedef uint32_t ResRefCount;
   typedef uint32_t ResId;
private:
   ResRefCount refCount;
   ResId resId;
   MapResMgr * resOwner;
public:
   Resource();
   Resource(Resource && src);
   Resource(const Resource & src);
   virtual ~Resource();

   virtual void decRefCount()
   {
      --refCount;
   }

   virtual ResRefCount getRefCount()
   {
      return refCount;
   }

   virtual void incRefCount()
   {
      ++refCount;
   }

   virtual ResId getResId()
   {
      return resId;
   }

   virtual void setResId(ResId newId)
   {
      resId = newId;
   }

   virtual void setResOwner(MapResMgr * newResOwner)
   {
      resOwner = newResOwner;
   }

   virtual MapResMgr * getResOwner()
   {
      return resOwner;
   }

   virtual QString getName();
};
}

#endif // RESOURCE_HPP
