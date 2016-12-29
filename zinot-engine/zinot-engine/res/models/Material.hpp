//
// Created by patryk on 27.05.16.
//

#ifndef ZINOTENGINEPROJECT_MATERIAL_HPP
#define ZINOTENGINEPROJECT_MATERIAL_HPP

#include <zinot-utils/zimesh-json/MaterialDao.hpp>
#include <zinot-engine/res-sys/MapResMgr.hpp>

namespace Zinot
{

class Material
{
public:
   Material();
   ~Material();

   bool loadFromZimeshJsonMaterialDao(const Zimesh::MaterialDao & materialDao, MapResMgr * gpuProgsMgr);
};
}


#endif //ZINOTENGINEPROJECT_MATERIAL_HPP
