//
// Created by patryk on 13.03.16.
//

#include "ConverterFactory.hpp"

#include <memory>
#include <zinot-textool/convert/PngConverter.hpp>
#include <zinot-textool/convert/ZitexConverter.hpp>

namespace Zinot
{
namespace Textool
{
Converter * ConverterFactory::createConverter(const QString & inFile)
{
   if (inFile.endsWith(".png"))
      return new PngConverter();
   else if (inFile.endsWith(".zitex"))
      return new ZitexConverter();
   else
      return nullptr;
}
}
}