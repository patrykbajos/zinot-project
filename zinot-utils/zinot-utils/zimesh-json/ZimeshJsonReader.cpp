//
// Created by patryk on 30.10.16.
//

#include "ZimeshJsonReader.hpp"

#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <zinot-utils/Logger.hpp>

namespace Zimesh
{

bool ZimeshJsonReader::loadFromJson(const std::string & filePath, ZimeshJsonDao & outData)
{
   QString fp = QString::fromStdString(filePath);

   QFile file(fp);
   if (!file.open(QIODevice::ReadOnly))
      return false;

   QByteArray bytes = file.readAll();
   QJsonParseError error;
   QJsonDocument doc = QJsonDocument::fromJson(bytes, &error);

   if (error.error != QJsonParseError::NoError)
   {
      auto & log = Logger::getInstance();
      log.log("[ERROR] Error loading model: " + fp + "\n" + error.errorString());
      return false;
   }

   if (!doc.isObject())
      return false;

   return outData.loadFromJsonObject(doc.object());
}
}