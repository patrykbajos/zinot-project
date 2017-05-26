//
// Created by patryk on 14.05.16.
//
#include "../../../../glloadgen/gl_core_3_3.hpp"
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

   dao.getMaterials();


   gl::GenBuffers(1, &dataBuf);
   gl::GenBuffers(1, &indexBuf);
   gl::BindBuffer(gl::ARRAY_BUFFER, dataBuf);
   gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, indexBuf);

   setLoaded(true);
   return true;
}

}