//
// Created by patryk on 12.03.16.
//

#include "Application.hpp"

#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>

#include <zinot-textool/conv/ConverterFactory.hpp>

namespace Zinot
{
namespace Textool
{
Application::Application(int argc, char ** argv) : coreApplication(argc, argv)
{
   coreApplication.setApplicationName("Zinottextool");
   coreApplication.setApplicationVersion("0.1");

   parseCmd();
   parseConfig();

   for (auto & file : cmdParser.positionalArguments())
   {
      std::unique_ptr<Converter> converter(ConverterFactory::createConverter(file));

      converter->convert(file, configuration);
   }
}

void Application::parseConfig()
{
   const QString & configPath = cmdParser.value("config");
   QFile configFile(configPath);

   configFile.open(QIODevice::ReadOnly | QIODevice::Text);
   QString content = configFile.readAll();
   configFile.close();

   QJsonParseError err;
   QJsonDocument configJson = QJsonDocument::fromJson(content.toUtf8(), &err);

   configuration.fromJsonObject(configJson.object());
}

void Application::parseCmd()
{
   cmdParser.setApplicationDescription("Textool converts png images to Zinot .tex format.");
   cmdParser.addHelpOption();
   cmdParser.addVersionOption();

   /*	Option -c or --config allows giving custom configuration.
    *	Positional argument files allows giving file or files to conversion.
    *	Output file resId will be the same but with changed extension.
    */
   cmdParser.addOption(QCommandLineOption({"c", "config"}, "Configuration in JSON", "config",
                                          "default-config.json"));
   cmdParser.addPositionalArgument("files", "List of files to convert");

   cmdParser.process(coreApplication);
}
}
}