#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <QMap>
#include <memory>
#include <zinot-engine/res-sys/NamesRegister.hpp>
#include <zinot-engine/res-sys/Resource.hpp>

namespace Zinot
{

class MapResMgr
{
public:
   template<class T>
   using ResPtr = std::shared_ptr<T>;
private:
   typedef QMap<Resource::ResId, ResPtr<Resource>> ContentContainer;

   ContentContainer content;
   NamesRegister namesRegister;
public:

   template<class T>
   /**
    * @brief Function gets or creates resource with specifed path.
    *
    * Function tries to find existing resource and return it. If resource
    * does not exists it creates new one and returns it.
    *
    * @param resPath Path (virtual or in File System) to resource.
    * @return Returns std::shared_ptr to resource.
    */
   ResPtr<T> getRes(const QString & resPath)
   {
      Resource::ResId resId = namesRegister.getId(resPath, true);
      ContentContainer::Iterator resIt = content.find(resId);

      // If resource doesn't exist, create it
      if (resIt == content.end())
      {
         ResPtr<Resource> resPtr(new T());
         resPtr->setResId(resId);
         resPtr->setResOwner(this);
         content.insert(resId, resPtr);
         return std::dynamic_pointer_cast<T>(resPtr);
      }

      return std::dynamic_pointer_cast<T>(resIt.value());
   }

   /** @brief Try delete resource. If deleted return true, otherwise return false.
    *
    * Tries delete resource pointer from content table. If pointer in table is not unique
    * it does nothing and returns false. If pointer with specified name or id does not exists
    * it returns false. If pointer is unique, function will delete it and will remove
    * name from register.
    *
    * @param resPath Path of resource.
    * @return Return true if deleted. Return false if there is no resource or resource is in use.
    */
   bool tryDeleteRes(const QString & resPath)
   {
      Resource::ResId resId = namesRegister.getId(resPath, false);
      ContentContainer::Iterator resIt = content.find(resId);

      // Resource found
      if (resIt != content.end())
      {
         // If there is not any pointer to resource (nobody using it)
         // then delete resource
         if (resIt.value().unique())
         {
            content.erase(resIt);
            return true;
         }
      }

      return false;
   }

   NamesRegister & getNamesRegister()
   {
      return namesRegister;
   }

   uint32_t getResourcesNum()
   {
      content.size();
   }
};
}

#endif // RESOURCEMANAGER_HPP
