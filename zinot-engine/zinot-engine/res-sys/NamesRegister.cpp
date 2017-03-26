//
// Created by patryk on 23.06.16.
//

#include "NamesRegister.hpp"

#include <QDirIterator>

namespace Zinot
{

NamesRegister::Id NamesRegister::getNewId()
{
   if (releasedId.isEmpty())
   {
      // First return, then increment next id
      return nextId++;
   }

   return releasedId.pop();
}

void NamesRegister::releaseId(Id id)
{
   if (id == (nextId - 1))
   {
      --nextId;
      return;
   }

   releasedId.push(id);
}

/*bool NamesRegister::addNamesFromPath(const QString & path)
{
   QDirIterator it(path,
                   QDir::Readable | QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks,
                   QDirIterator::Subdirectories);

   while (it.hasNext())
      addName(QDir::cleanPath(it.next()));
}*/

bool NamesRegister::deleteName(const QString & name)
{
   NameToIdContainer::iterator nameToIdIt = nameToId.find(name);
   if (nameToIdIt == nameToId.end())
      return false;

   IdToNameContainer::iterator idToNameIt = idToName.find(nameToIdIt.value());
   if (idToNameIt == idToName.end())
      return false;

   releaseId(nameToIdIt.value());

   idToName.erase(idToNameIt);
   nameToId.erase(nameToIdIt);

   return true;
}

bool NamesRegister::deleteId(Id nameId)
{
   IdToNameContainer::iterator idToNameIt = idToName.find(nameId);
   if (idToNameIt == idToName.end())
      return false;

   NameToIdContainer::iterator nameToIdIt = nameToId.find(idToNameIt.value());
   if (nameToIdIt == nameToId.end())
      return false;

   releaseId(nameToIdIt.value());

   idToName.erase(idToNameIt);
   nameToId.erase(nameToIdIt);

   return true;
}

QString NamesRegister::getName(Id nameId) const
{
   if (nameId == 0)
      return QString();

   IdToNameContainer::const_iterator it = idToName.find(nameId);

   if (it == idToName.end())
      return QString();

   return QString(it.value());
}

NamesRegister::Id NamesRegister::getId(const QString & name, bool autoCreate)
{
   NameToIdContainer::const_iterator it = nameToId.find(name);

   if (it == nameToId.end())
   {
      if (!autoCreate)
         return 0;

      Id newId = getNewId();

      nameToId.insert(name, newId);
      idToName.insert(newId, name);

      return newId;
   }

   return it.value();
}
}