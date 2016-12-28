//
// Created by patryk on 13.03.16.
//

#ifndef ZINOTENGINEPROJECT_CONVERTERFACTORY_HPP
#define ZINOTENGINEPROJECT_CONVERTERFACTORY_HPP

#include <QString>
#include <zinot-textool/convert/Converter.hpp>

namespace Zinot
{
namespace Textool
{
class ConverterFactory
{
public:
   static Converter * createConverter(const QString & inFile);
};
}
}

#endif //ZINOTENGINEPROJECT_CONVERTERFACTORY_HPP
