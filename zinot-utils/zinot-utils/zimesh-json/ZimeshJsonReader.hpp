//
// Created by patryk on 30.10.16.
//

#ifndef ZINOT_PROJECT_READER_HPP
#define ZINOT_PROJECT_READER_HPP

#include <string>
#include <zinot-utils/zimesh-json/ZimeshJsonDao.hpp>

namespace Zimesh
{

class ZimeshJsonReader
{
public:
   static bool loadFromJson(const std::string & filePath, ZimeshJsonDao & outData);
};

}

#endif //ZINOT_PROJECT_READER_HPP
