//
// Created by patryk on 14.07.16.
//

#include "SceneDao.hpp"

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>

#include <zinot-utils/Logger.hpp>
#include <zinot-engine/res/GpuProgram.hpp>
#include <zinot-engine/scene/dao/ShaderDao.hpp>
#include <zinot-engine/scene/dao/ObjectDao.hpp>

namespace Zinot
{

bool SceneDao::loadFromJSON(const QString & filePath)
{
   QFile file(filePath);
   file.open(QIODevice::ReadOnly);
   QJsonParseError jsonParseError;
   QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll(), &jsonParseError);
   file.close();

   Logger & log = Logger::getInstance();

   if (jsonParseError.error)
   {
      log.log("(ERROR): Parsing scene \"" + filePath + "\". Error string:\n" + jsonParseError.errorString());
      return false;
   }

   if (jsonDoc.isEmpty())
   {
      log.log("(ERROR): SceneDao .json document \"" + filePath + "\" is empty.");
      return false;
   }

   if (!jsonDoc.isObject())
   {
      log.log("(ERROR): SceneDao .json document \"" + filePath + "\" has content not being JSON object.");
      return false;
   }

   if (!parse(jsonDoc.object()))
   {
      log.log("[ERROR]: Parsing scene done with error! SceneDao not loaded...");
      return false;
   }

   return true;
}

bool SceneDao::parse(const QJsonObject & mainObj)
{
   QJsonValue shadersVal = mainObj["shaders"];
   QJsonValue objectsVal = mainObj["objects"];
   QJsonValue cameraVal = mainObj["camera"];
   if (!shadersVal.isArray() || !objectsVal.isArray() || !cameraVal.isObject())
      return false;

   if (!parseShaders(shadersVal.toArray()))
      return false;

   if (!parseObjects(objectsVal.toArray()))
      return false;

   if(!parseMainCamera(cameraVal.toObject()))
      return false;

   return true;
}

bool SceneDao::parseShaders(const QJsonArray & shadersArr)
{
   shadersDao.clear();
   shadersDao.reserve(shadersArr.size());

   for (const QJsonValue & shaderVal : shadersArr)
   {
      if (!shaderVal.isObject())
         continue;

      ShaderDao shaderDao;
      if (!shaderDao.parseObject(shaderVal.toObject()))
         continue;

      shadersDao.push_back(std::move(shaderDao));
   }

   shadersDao.squeeze();
   return true;
}

bool SceneDao::parseObjects(const QJsonArray & objectsArr)
{
   objectsDao.clear();
   objectsDao.reserve(objectsArr.size());

   for (const QJsonValue & objectVal : objectsArr)
   {
      if (!objectVal.isObject())
         continue;

      ObjectDao objectDao;
      if (!objectDao.parseObject(objectVal.toObject()))
         continue;

      objectsDao.push_back(std::move(objectDao));
   }

   objectsDao.squeeze();
   return true;
}

bool SceneDao::parseMainCamera(const QJsonObject & cameraObj)
{
   return mainCam.parseObject(cameraObj);
}
}

