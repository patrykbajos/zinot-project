//
// Created by patryk on 14.05.16.
//

#ifndef ZINOTENGINEPROJECT_MODEL_HPP
#define ZINOTENGINEPROJECT_MODEL_HPP

#include <GL/gl.h>
#include <zinot-engine/res-sys/Resource.hpp>

namespace Zinot
{

class Material;

class Model : public Resource
{
private:
   GLuint indexBuf;
   GLuint dataBuf;
   QMap<QString, Material> materials;
public:
   Model(){
      setLoaded(false);
   }
   virtual ~Model() override;

   bool loadFromFile(const QString & fp);
};

}

#endif //ZINOTENGINEPROJECT_MODEL_HPP
