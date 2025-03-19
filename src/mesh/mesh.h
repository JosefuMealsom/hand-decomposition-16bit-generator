#pragma once
// How to forward declare this?
#include <vector>

struct Vertex;
namespace Component
{
  class IndexedMesh;
}

class Mesh
{
public:
  std::vector<Vertex> m_Vertices;
  std::vector<unsigned int> m_Indices;

  static Component::IndexedMesh Generate(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices);
  Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);

private:
  unsigned int m_VAO, m_VBO, m_EBO;
  void SetupMesh();
};
