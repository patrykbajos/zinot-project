//
// Created by patryk on 14.05.16.
//

#ifndef ZINOTENGINEPROJECT_MODEL_HPP
#define ZINOTENGINEPROJECT_MODEL_HPP

#include <GL/gl.h>
#include <assimp/scene.h>

#include <zinot-engine/res-sys/Resource.hpp>
#include <zinot-engine/res/models/Mesh.hpp>
#include <zinot-engine/res/Texture.hpp>
#include <zinot-engine/res/models/ModelNode.hpp>
#include <zinot-engine/res/models/Material.hpp>

namespace Zinot
{
class Model : public Resource
{
public:
   typedef glm::vec3 VertexPos;
   typedef glm::vec3 Normal;
   typedef glm::vec2 TexCoord;

   typedef glm::vec3 Tangent;
   typedef glm::vec3 Bitangent;

   struct Vertex
   {
      VertexPos vert;
      Normal normal;
      TexCoord uv;
   };
   struct VertexNormalMap : VertexPos
   {
      Tangent tan;
      Bitangent bi;
   };

   typedef glm::i16vec3 Triangle;
protected:
   GLuint vbo = 0;
   GLuint ebo = 0;
   uint32_t vertsNum = 0;
   uint32_t trisNum = 0;

   uint32_t meshesNum = 0;
   Mesh * meshes = nullptr;

   uint32_t materialsNum = 0;
   Material * materials = nullptr;

   uint32_t nodesNum = 0;
   ModelNode * nodes = nullptr;
   ModelNode * rootNode = nullptr;

   uint32_t countVerticesInScene(const aiScene * scene);
   uint32_t countFacesInScene(const aiScene * scene);
   bool processScene(const aiScene * scene, MapResMgr * texResMgr);

   bool processMeshes(const aiScene * scene);
   bool processVertices(const aiScene * scene);
   bool processTriangles(const aiScene * scene);

   bool processMaterials(const aiScene * scene, MapResMgr * texResMgr);
public:
   ~Model();
   bool loadFromFile(MapResMgr * texResMgr);
   bool draw(GLuint program);
};
}

#endif //ZINOTENGINEPROJECT_MODEL_HPP
