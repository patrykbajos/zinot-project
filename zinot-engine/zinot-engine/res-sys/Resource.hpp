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
   typedef uint32_t ResId;
private:
   ResId resId = 0;
   MapResMgr * resOwner = nullptr;
   bool loaded;
protected:
   void setLoaded(bool loaded);
public:
   virtual ~Resource();

   virtual ResId getResId()
   {
      return resId;
   }

   virtual void setResId(ResId resId)
   {
      Resource::resId = resId;
   }

   virtual void setResOwner(MapResMgr * resOwner)
   {
      Resource::resOwner = resOwner;
   }

   virtual MapResMgr * getResOwner()
   {
      return resOwner;
   }

   bool isLoaded() const;
   virtual QString getName();
};
}

#endif // RESOURCE_HPP
