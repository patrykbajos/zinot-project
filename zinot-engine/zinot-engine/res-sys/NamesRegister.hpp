//
// Created by patryk on 23.06.16.
//

#ifndef ZINOTENGINEPROJECT_NAMESREGISTER_HPP
#define ZINOTENGINEPROJECT_NAMESREGISTER_HPP

#include <QMap>
#include <QString>
#include <QStack>

namespace Zinot
{

class NamesRegister
{
public:
   typedef uint32_t NameId;
   typedef QString Name;
protected:
   typedef QMap<QString, NameId> NameToIdContainer;
   typedef QMap<NameId, QString> IdToNameContainer;
   NameToIdContainer nameToId;
   IdToNameContainer idToName;

   QStack<NameId> releasedId;
   NameId nextId = 1;

   NameId getNewId();
   void releaseId(NameId id);
public:
   //bool addNamesFromPath(const QString & path);

   bool deleteName(const Name & name);
   bool deleteId(NameId nameId);

   Name getName(NameId nameId) const;
   NameId getId(const Name & name, bool autoCreate = true);
};
}

#endif //ZINOTENGINEPROJECT_NAMESREGISTER_HPP
