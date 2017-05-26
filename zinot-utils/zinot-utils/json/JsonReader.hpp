//
// Created by patryk on 30.10.16.
//

#ifndef ZINOT_PROJECT_READER_HPP
#define ZINOT_PROJECT_READER_HPP

#include <QString>
#include <zinot-utils/json/JsonDao.hpp>

namespace Zinot
{

class JsonReader
{
public:
   static bool loadFromJsonFile(const QString & filePath, JsonDao & outDao);
};
}

#endif //ZINOT_PROJECT_READER_HPP
