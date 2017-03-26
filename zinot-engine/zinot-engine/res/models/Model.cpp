//
// Created by patryk on 14.05.16.
//
#include <gl_core_3_3.hpp>
#include "Model.hpp"

#include <zinot-utils/Logger.hpp>
#include <zinot-utils/json/JsonReader.hpp>
#include <zinot-utils/zimesh-json/ZimeshJsonDao.hpp>

namespace Zinot
{

Model::~Model()
{
}

bool Model::loadFromFile()
{
   Logger & logger = Logger::getInstance();
   QString fp = getName();

   Zimesh::ZimeshJsonDao dao;

   if (!JsonReader::loadFromJsonFile(fp, dao))
   {
      logger.log("[ERROR]: Cannot load model: " + fp);
      return false;
   }

   // TODO: Perform loading model into OpenGL

   setLoaded(true);
   return true;
}

}