//
// Created by patryk on 13.03.16.
//

#ifndef ZINOTENGINEPROJECT_CONVERTER_HPP
#define ZINOTENGINEPROJECT_CONVERTER_HPP

#include <zinot-textool/conf/Configuration.hpp>

class QString;

namespace Zinot
{
namespace Textool
{
class Converter
{
public:
   virtual ~Converter()
   { };
   virtual bool convert(const QString & inFile, const Configuration & configuration) = 0;
};
}
}


#endif //ZINOTENGINEPROJECT_CONVERTER_HPP
