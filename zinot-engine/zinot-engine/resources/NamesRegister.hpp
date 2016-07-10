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
   NameId addName(const QString & name);
   bool addNamesFromPath(const QString & path);

   bool deleteName(const QString & name);
   bool deleteId(NameId nameId);

   QString getName(NameId nameId) const;
   NameId getId(const QString & name) const;
};
}

#endif //ZINOTENGINEPROJECT_NAMESREGISTER_HPP
