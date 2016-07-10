#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <zinot-engine/resources/NamesRegister.hpp>
#include <QMap>

namespace Zinot
{
class Resource;

class MapResMgr
{
public:
   typedef uint32_t ResRefCount;
   typedef uint32_t ResName;
protected:
   typedef QMap<ResName, Resource *> ContentContainer;
   ContentContainer content;

   NamesRegister namesRegister;
public:
   ~MapResMgr();

   Resource * getRes(ResName name);
   Resource * newRes(ResName name, Resource * newRes, bool autoDestroy);
   void deleteRes(ResName nameId);

   NamesRegister & getNamesRegister()
   { return namesRegister; }
};
}

#endif // RESOURCEMANAGER_HPP
