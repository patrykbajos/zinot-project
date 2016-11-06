//
// Created by patryk on 30.10.16.
//

#ifndef ZINOT_PROJECT_READER_HPP
#define ZINOT_PROJECT_READER_HPP

#include <string>

#include <zinot-utils/zimesh-json/JSONData.hpp>

namespace Zimesh
{

class JSONReader
{
public:
   bool loadFromJSON(const std::string & filePath, JSONData & outData) const;
};

}

#endif //ZINOT_PROJECT_READER_HPP
