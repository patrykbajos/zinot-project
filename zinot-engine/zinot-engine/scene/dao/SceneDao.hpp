//
// Created by patryk on 14.07.16.
//

#ifndef ZINOT_PROJECT_SCENE_HPP
#define ZINOT_PROJECT_SCENE_HPP

#include <gl_core_3_3.hpp>

#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <zinot-engine/res-sys/MapResMgr.hpp>
#include <zinot-engine/scene/dao/ShaderDao.hpp>
#include <zinot-engine/scene/dao/ObjectDao.hpp>
#include <zinot-engine/scene/dao/CameraDao.hpp>
#include <zinot-engine/scene/GameObject.hpp>
#include <zinot-engine/eng/FPSCamera.hpp>

namespace Zinot
{

class SceneDao
{
protected:
   CameraDao mainCam;
   QVector<ShaderDao> shadersDao;
   QVector<ObjectDao> objectsDao;

   bool parse(const QJsonObject & mainObj);
   bool parseShaders(const QJsonArray & shadersArr);
   bool parseObjects(const QJsonArray & objectsArr);
   bool parseMainCamera(const QJsonObject & cameraObj);
public:
   bool loadFromJSON(const QString & filePath);

   const CameraDao & getMainCam() const
   {
      return mainCam;
   }

   const QVector<ShaderDao> & getShadersDao() const
   {
      return shadersDao;
   }

   const QVector<ObjectDao> & getObjectsDao() const
   {
      return objectsDao;
   }
};
}

#endif //ZINOT_PROJECT_SCENE_HPP
