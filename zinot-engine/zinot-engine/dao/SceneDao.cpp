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
#include <zinot-engine/res/Shader.hpp>
#include <zinot-engine/dao/ShaderDescDao.hpp>
#include <zinot-engine/dao/ObjectDao.hpp>

namespace Zinot
{

bool SceneDao::loadFromJsonDoc(const QJsonDocument & jsonDoc)
{
   return true;
}
}

