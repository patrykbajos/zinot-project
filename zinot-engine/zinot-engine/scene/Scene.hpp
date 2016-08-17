//
// Created by patryk on 14.07.16.
//

#ifndef ZINOT_PROJECT_SCENE_HPP
#define ZINOT_PROJECT_SCENE_HPP

#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <zinot-engine/res-sys/MapResMgr.hpp>
#include <zinot-engine/scene/ShaderDao.hpp>
#include <zinot-engine/scene/ObjectDao.hpp>
#include <zinot-engine/scene/CameraDao.hpp>

namespace Zinot
{

class Scene
{
private:
   bool parse(const QJsonObject & mainObj, QVector<ShaderDao> & shadersDaoVec, QVector<ObjectDao> & objectsDaoVec);

   bool parseShaders(const QJsonArray & shadersArr, QVector<ShaderDao> & shadersDaoVec);
   bool parseObjects(const QJsonArray & objectsArr, QVector<ObjectDao> & objectsDaoVec);
   bool parseCamera(const QJsonObject & cameraObj, CameraDao & cameraDao);

   bool loadData(const QVector<ShaderDao> & shadersDaoVec,
                 const CameraDao & cameraDao,
                 const QVector<ObjectDao> & objectsDaoVec);
public:
   struct ResourceManagers
   {
      MapResMgr * gpuProgMgr;
      MapResMgr * vsMgr;
      MapResMgr * fsMgr;
      MapResMgr * modelsMgr;
      MapResMgr * texturesMgr;
   };
   ResourceManagers res;

   bool loadFromJSON(const QString & filePath);
};
}

#endif //ZINOT_PROJECT_SCENE_HPP
