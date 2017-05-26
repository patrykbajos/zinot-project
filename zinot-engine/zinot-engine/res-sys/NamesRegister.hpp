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

/**
 * @brief Class implamenting relations id to name and name to id
 *
 * Class contains map of names pointing to generated id's and conteiner
 * containging map of id's pointing to names. It generates id's
 * 1 =< id. Id 0 means void id.
 */
class NamesRegister
{
public:
   typedef uint32_t Id; ///< Type of ID. It is unsigned 32b value.
   typedef QString Name; ///< Type of Name. It is Qt5 string. It is using shared data.
protected:
   typedef QMap<QString, Id> NameToIdContainer;
   typedef QMap<Id, QString> IdToNameContainer;
   NameToIdContainer nameToId;
   IdToNameContainer idToName;

   QStack<Id> releasedId;
   Id nextId = 1;

   Id getNewId();
   void releaseId(Id id);
public:
   bool deleteName(const Name & name);
   bool deleteId(Id nameId);

   Name getName(Id nameId) const;
   Id getId(const Name & name, bool autoCreate = true);
};
}

#endif //ZINOTENGINEPROJECT_NAMESREGISTER_HPP
