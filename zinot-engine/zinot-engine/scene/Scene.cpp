//
// Created by patryk on 14.07.16.
//

#include "Scene.hpp"
#include <gl_core_3_3.hpp>

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>

#include <zinot-utils/Logger.hpp>
#include <zinot-engine/res/GpuProgram.hpp>
#include <zinot-engine/res/Shader.hpp>
#include <zinot-engine/scene/ShaderDao.hpp>
#include <zinot-engine/scene/ObjectDao.hpp>

namespace Zinot
{

bool Scene::loadFromJSON(const QString & filePath)
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
      log.log("(ERROR): Json document \"" + filePath + "\" is empty.");
      return false;
   }

   if (!jsonDoc.isObject())
   {
      log.log("(ERROR): Json document \"" + filePath + "\" is not object.");
      return false;
   }

   QVector<ShaderDao> shadersDaoVec;
   QVector<ObjectDao> objectsDaoVec;
   parse(jsonDoc.object(), shadersDaoVec, objectsDaoVec);

   for (uint32_t it = 0; it < shadersDaoVec.size(); ++it)
   {
      const auto & shad = shadersDaoVec[it];
      log.log("(INFO): Shader[" + QString::number(it) + "]{name = " + shad.getName() \
 + ", vs = " + shad.getVs() \
 + ", fs = " + shad.getFs() + " }");
   }
   for (uint32_t it = 0; it < objectsDaoVec.size(); ++it)
   {
      const auto & obj = objectsDaoVec[it];
      log.log("(INFO): Obj[" + QString::number(it) + "]{model = " + obj.getModel() \
 + ", shader = " + obj.getShader() + " }");
   }


   return true;
}

bool Scene::parse(const QJsonObject & mainObj,
                  QVector<ShaderDao> & shadersDaoVec,
                  QVector<ObjectDao> & objectsDaoVec)
{
   QJsonValue shadersVal = mainObj["shaders"];
   QJsonValue objectsVal = mainObj["objects"];
   if (!shadersVal.isArray() || !objectsVal.isArray())
      return false;

   if (!parseShaders(shadersVal.toArray(), shadersDaoVec))
      return false;

   if (!parseObjects(objectsVal.toArray(), objectsDaoVec))
      return false;

   return true;
}

bool Scene::parseShaders(const QJsonArray & shadersArr, QVector<ShaderDao> & shadersDaoVec)
{
   shadersDaoVec.clear();
   shadersDaoVec.reserve(shadersArr.size());

   for (const QJsonValue & shaderVal : shadersArr)
   {
      if (!shaderVal.isObject())
         continue;

      ShaderDao shaderDao;
      if (!shaderDao.parseObject(shaderVal.toObject()))
         continue;

      shadersDaoVec.push_back(std::move(shaderDao));
   }

   shadersDaoVec.squeeze();
   return true;
}

bool Scene::parseObjects(const QJsonArray & objectsArr, QVector<ObjectDao> & objectsDaoVec)
{
   objectsDaoVec.clear();
   objectsDaoVec.reserve(objectsArr.size());

   for (const QJsonValue & objectVal : objectsArr)
   {
      if (!objectVal.isObject())
         continue;

      ObjectDao objectDao;
      if (!objectDao.parseObject(objectVal.toObject()))
         continue;

      objectsDaoVec.push_back(std::move(objectDao));
   }

   objectsDaoVec.squeeze();
   return true;
}

bool Scene::parseCamera(const QJsonObject & cameraObj, CameraDao & cameraDao)
{
   return false;
}

bool Scene::loadData(const QVector<ShaderDao> & shadersDaoVec,
                     const CameraDao & cameraDao,
                     const QVector<ObjectDao> & objectsDaoVec)
{
   return false;
}
}

