#include "loader.h"
#include "pch/pch.h"
#include "scene/components/indexed_mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include "logger.h"
#include "mesh/mesh.h"
#include <vector>
#include "mesh/vertex.h"
#include <glm/vec3.hpp>

Component::IndexedMesh Mesh::Loader::LoadMeshFromFile(const std::string &path)
{
  Assimp::Importer importer;
  const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

  LOG_INFO("Number of meshes: {}", scene->mNumMeshes);

  if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
  {
    LOG_ERROR("ERROR::ASSIMP::{}", importer.GetErrorString());
  }

  LOG_INFO("Model {} successfully loaded", path);

  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;

  // Assuming path only contains 1 mesh for now
  aiMesh *mesh = scene->mMeshes[0];

  // LOG_INFO("Vertices: {}", mesh->mNumVertices);
  // LOG_INFO("texcoords: {}", mesh->mTextureCoords);

  Vertex vertex;

  for (int i = 0; i < mesh->mNumVertices; i++)
  {
    glm::vec3 vector;
    vector.x = mesh->mVertices[i].x;
    vector.y = mesh->mVertices[i].y;
    vector.z = mesh->mVertices[i].z;
    vertex.Position = vector;

    vector.x = mesh->mNormals[i].x;
    vector.y = mesh->mNormals[i].y;
    vector.z = mesh->mNormals[i].z;
    vertex.Normal = vector;

    vector.x = mesh->mTextureCoords[0][i].x;
    vector.y = mesh->mTextureCoords[0][i].y;
    vertex.TexCoords = vector;

    vertices.push_back(vertex);
  }

  for (unsigned int i = 0; i < mesh->mNumFaces; i++)
  {
    aiFace face = mesh->mFaces[i];
    for (unsigned int j = 0; j < face.mNumIndices; j++)
      indices.push_back(face.mIndices[j]);
  }

  return Mesh::Generate(vertices, indices);
}
