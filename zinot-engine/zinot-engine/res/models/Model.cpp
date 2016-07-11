//
// Created by patryk on 14.05.16.
//
#include <gl_core_3_3.hpp>
#include "Model.hpp"

#include <assimp/cimport.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <glm/gtc/type_ptr.hpp>

namespace Zinot
{

Model::~Model()
{
   if (meshes)
      delete[] meshes;

   if (materials)
      delete[] materials;

   if (nodes)
      delete[] nodes;
}

bool Model::loadFromFile(MapResMgr * texResMgr)
{
   const aiScene * scene = aiImportFile(getName().toStdString().c_str(),
                                        aiProcess_JoinIdenticalVertices | aiProcess_Triangulate
                                        | aiProcess_SortByPType);

   if (!scene)
      return false;

   // If nothing to do
   if (!scene->HasMeshes())
      return true;

   if (!processScene(scene, texResMgr))
      return false;

   return true;
}

bool Model::processScene(const aiScene * scene, MapResMgr * texResMgr)
{
   if (!processMeshes(scene))
      return false;
   if (!processMaterials(scene, texResMgr))
      return false;

   return true;
}

bool Model::processMaterials(const aiScene * scene, MapResMgr * texResMgr)
{
   materialsNum = scene->mNumMaterials;
   materials = new Material[materialsNum];

   aiMaterial ** aiMaterials = scene->mMaterials;
   QString modelDir = getName().section("/", 0, -2);
   std::string strmodeldir = modelDir.toStdString();

   for (uint32_t matIt = 0; matIt < materialsNum; ++matIt)
   {
      aiMaterial * aiMaterial = aiMaterials[matIt];
      Material & material = materials[matIt];
      if (!material.processAiMaterial(modelDir, aiMaterial, texResMgr))
         return false;
   }

   return true;
}

bool Model::processMeshes(const aiScene * scene)
{
   vertsNum = countVerticesInScene(scene);
   trisNum = countFacesInScene(scene);

   meshesNum = scene->mNumMeshes;
   meshes = new Mesh[meshesNum];

   if (!processVertices(scene))
      return false;
   if (!processTriangles(scene))
      return false;

   return true;
}

bool Model::processVertices(const aiScene * scene)
{
   uint32_t vertSize = sizeof(Vertex);

   gl::GenBuffers(1, &vbo);
   if (!vbo)
      return false;

   gl::BindBuffer(gl::ARRAY_BUFFER, vbo);
   gl::BufferData(gl::ARRAY_BUFFER, vertsNum * vertSize, nullptr, gl::STATIC_DRAW);

   // for meshes in scene
   for (uint32_t meshIt = 0, baseVert = 0; meshIt < meshesNum; ++meshIt)
   {
      aiMesh * aiMesh = scene->mMeshes[meshIt];
      Mesh & mesh = meshes[meshIt];

      uint32_t meshVertsNum = aiMesh->mNumVertices;
      mesh.baseVertex = baseVert;

      // for vertices in mesh
      for (uint32_t meshVertIt = 0; meshVertIt < meshVertsNum; ++meshVertIt)
      {
         Vertex vert;
         auto & vertPos = aiMesh->mVertices[meshVertIt];
         auto & vertNorm = aiMesh->mNormals[meshVertIt];
         auto & vertUv = aiMesh->mTextureCoords[0][meshVertIt];

         vert.vert = glm::vec3(vertPos.x, vertPos.y, vertPos.z);
         vert.normal = glm::vec3(vertNorm.x, vertNorm.y, vertNorm.z);
         vert.uv = glm::vec2(vertUv.x, vertUv.y);

         uint32_t globVertIt = baseVert + meshVertIt;
         gl::BufferSubData(gl::ARRAY_BUFFER, globVertIt * vertSize, vertSize, &vert);
      }

      baseVert += meshVertsNum;
   }

   gl::BindBuffer(gl::ARRAY_BUFFER, 0);

   return true;
}

bool Model::processTriangles(const aiScene * scene)
{
   uint32_t triSize = sizeof(Triangle);

   gl::GenBuffers(1, &ebo);
   if (!ebo)
      return false;

   gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, ebo);
   gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, trisNum * triSize, nullptr, gl::STATIC_DRAW);

   for (uint32_t meshIt = 0, baseTri = 0; meshIt < meshesNum; ++meshIt)
   {
      const aiMesh * aiMesh = scene->mMeshes[meshIt];
      Mesh & mesh = meshes[meshIt];

      uint32_t meshTrisNum = aiMesh->mNumFaces;
      mesh.count = meshTrisNum * 3; // Indices num. For each face are 3 indices
      mesh.indices = baseTri * triSize; // Offset in bytes
      mesh.type = gl::UNSIGNED_SHORT;
      mesh.matIt = aiMesh->mMaterialIndex;

      for (uint32_t meshTriIt = 0; meshTriIt < aiMesh->mNumFaces; ++meshTriIt)
      {
         auto * indArr = aiMesh->mFaces[meshTriIt].mIndices;
         Triangle tri(indArr[0], indArr[1], indArr[2]);

         gl::BufferSubData(gl::ELEMENT_ARRAY_BUFFER,
                           (baseTri + meshTriIt) * triSize, // Offset in bytes
                           triSize,
                           glm::value_ptr(tri));
      }

      baseTri += meshTrisNum;
   }

   gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, 0);

   return true;
}

bool Model::draw(GLuint program)
{
   gl::BindBuffer(gl::ARRAY_BUFFER, vbo);
   gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, ebo);

   gl::EnableVertexAttribArray(0);
   gl::EnableVertexAttribArray(1);
   gl::EnableVertexAttribArray(2);

   uint32_t vertSize = sizeof(Vertex);
   uint32_t posSize = sizeof(VertexPos);
   uint32_t normSize = sizeof(Normal);
   uint32_t uvSize = sizeof(TexCoord);

   gl::VertexAttribPointer(0, 3, gl::FLOAT, gl::FALSE_,
                           vertSize, nullptr); // Pos  vec3
   gl::VertexAttribPointer(1, 3, gl::FLOAT, gl::FALSE_,
                           vertSize, (void *) posSize); // Norm vec3
   gl::VertexAttribPointer(2, 2, gl::FLOAT, gl::FALSE_,
                           vertSize, (void *) (posSize + normSize)); // Uv   vec2

   GLint texDiffLoc = gl::GetUniformLocation(program, "texDiff");

   for (uint32_t it = 0; it < meshesNum; ++it)
   {
      const Mesh & mesh = meshes[it];

      gl::ActiveTexture(gl::TEXTURE0);
      GLuint texDiff = materials[mesh.matIt].getTexDiff()->getId();
      gl::BindTexture(gl::TEXTURE_2D, texDiff);
      gl::Uniform1i(texDiffLoc, 0);

      gl::DrawElementsBaseVertex(gl::TRIANGLES, mesh.count, mesh.type,
                                 (void *) mesh.indices, mesh.baseVertex);
   }

   gl::DisableVertexAttribArray(2);
   gl::DisableVertexAttribArray(1);
   gl::DisableVertexAttribArray(0);

   gl::BindBuffer(gl::ARRAY_BUFFER, 0);
   gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, 0);

   return true;
}

uint32_t Model::countVerticesInScene(const aiScene * scene)
{
   uint32_t verticesNum = 0;

   for (uint32_t it = 0; it < scene->mNumMeshes; ++it)
   {
      verticesNum += scene->mMeshes[it]->mNumVertices;
   }

   return verticesNum;
}

uint32_t Model::countFacesInScene(const aiScene * scene)
{
   uint32_t facesNum = 0;

   for (uint32_t it = 0; it < scene->mNumMeshes; ++it)
   {
      facesNum += scene->mMeshes[it]->mNumFaces;
   }

   return facesNum;
}
}