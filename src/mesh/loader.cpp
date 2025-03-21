#include "loader.h"
#include "pch/pch.h"
#include "scene/components/indexed_mesh.h"
#include <assimp/cimport.h>
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
  // Using function version due to unresolved symbol while linking on windows.
  const aiScene *scene = aiImportFile(path.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs);

  if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
  {
    LOG_ERROR("ERROR::ASSIMP::{}", aiGetErrorString());
  }

  LOG_INFO("Model {} successfully loaded", path);

  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;

  // Assuming path only contains 1 mesh for now
  aiMesh *mesh = scene->mMeshes[0];

  for (int i = 0; i < mesh->mNumVertices; i++)
  {
    Vertex vertex;

    glm::vec3 position;
    position.x = mesh->mVertices[i].x;
    position.y = mesh->mVertices[i].y;
    position.z = mesh->mVertices[i].z;
    vertex.Position = position;

    glm::vec3 normals;
    normals.x = mesh->mNormals[i].x;
    normals.y = mesh->mNormals[i].y;
    normals.z = mesh->mNormals[i].z;
    vertex.Normal = normals;

    glm::vec2 texCoords;
    texCoords.x = mesh->mTextureCoords[0][i].x;
    texCoords.y = mesh->mTextureCoords[0][i].y;
    vertex.TexCoords = texCoords;

    vertices.push_back(vertex);
  }

  for (unsigned int i = 0; i < mesh->mNumFaces; i++)
  {
    aiFace face = mesh->mFaces[i];
    for (unsigned int j = 0; j < face.mNumIndices; j++)
      indices.push_back(face.mIndices[j]);
  }

  aiReleaseImport(scene);
  return Mesh::Generate(vertices, indices);
}
