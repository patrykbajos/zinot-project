//
// Created by patryk on 12.03.16.
//

#ifndef ZINOTENGINEPROJECT_APPLICATION_HPP
#define ZINOTENGINEPROJECT_APPLICATION_HPP

#include <QCoreApplication>
#include <QCommandLineParser>
#include <zinot-textool/config/ConfigDao.hpp>

namespace Zinot
{
namespace Textool
{
class Application
{
   QCoreApplication coreApplication;
   QCommandLineParser cmdParser;
   ConfigDao configuration;

   void parseCmd();

   void parseConfig();

public:
   Application(int argc, char * argv[]);
};
}
}

#endif //ZINOTENGINEPROJECT_APPLICATION_HPP
