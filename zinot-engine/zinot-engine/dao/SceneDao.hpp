//
// Created by patryk on 14.07.16.
//

#ifndef ZINOT_PROJECT_SCENE_HPP
#define ZINOT_PROJECT_SCENE_HPP

//#include <gl_core_3_3.hpp>

#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <zinot-engine/res-sys/MapResMgr.hpp>
#include <zinot-engine/dao/ShaderDescDao.hpp>
#include <zinot-engine/dao/ObjectDao.hpp>
#include <zinot-engine/dao/CameraDao.hpp>
#include <zinot-engine/scene/GameObject.hpp>
#include <zinot-engine/eng/FPSCamera.hpp>
#include <zinot-utils/json/JsonDao.hpp>

namespace Zinot
{

class SceneDao : public JsonDao
{
protected:
   CameraDao mainCam;
   QVector<ShaderDescDao> shadersDao;
   QVector<ObjectDao> objectsDao;
public:
   virtual bool loadFromJsonDoc(const QJsonDocument & jsonDoc) override;
};
}

#endif //ZINOT_PROJECT_SCENE_HPP
