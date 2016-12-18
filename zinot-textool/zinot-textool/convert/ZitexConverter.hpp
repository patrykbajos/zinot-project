//
// Created by patryk on 24.04.16.
//

#ifndef ZINOTENGINEPROJECT_ZITEXCONVERTER_HPP
#define ZINOTENGINEPROJECT_ZITEXCONVERTER_HPP

#include <vector>
#include <memory>

#include <zinot-textool/convert/Converter.hpp>
#include <zinot-textool/convert/Mipmap.hpp>

namespace Zinot
{
namespace Textool
{
class ZitexConverter : public Converter
{
public:
   virtual bool convert(const QString & inFileName, const ConfigDao & configuration) override;
};
}
};


#endif //ZINOTENGINEPROJECT_ZITEXCONVERTER_HPP
