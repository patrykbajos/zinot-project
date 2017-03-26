//
// Created by patryk on 10.01.17.
//
#include "JsonReader.hpp"

#include <QFile>
#include <zinot-utils/Logger.hpp>

namespace Zinot
{

bool JsonReader::loadFromJsonFile(const QString & filePath, JsonDao & outData)
{
   QFile file(filePath);
   if (!file.open(QIODevice::ReadOnly))
      return false;

   QByteArray bytes = file.readAll();
   QJsonParseError error;
   QJsonDocument doc = QJsonDocument::fromJson(bytes, &error);

   if (error.error != QJsonParseError::NoError)
   {
      auto & log = Logger::getInstance();
      log.log("[ERROR] Error loading JSON document: " + filePath + "\n" + error.errorString());
      return false;
   }

   return outData.loadFromJsonDoc(doc);
}
}