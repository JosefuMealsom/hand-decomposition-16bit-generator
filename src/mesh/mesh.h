#pragma once
// How to forward declare this?
#include <vector>

struct Vertex;
namespace Component
{
  class IndexedMesh;
}

namespace Mesh
{
  Component::IndexedMesh Generate(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices);
};
