#pragma once

#include "pch/pch.h"
#include <glm/vec3.hpp>

namespace Component
{

  struct IndexedMesh
  {
    uint32_t vao_id;
    unsigned int NumVertices;
    unsigned int NumIndices;

    IndexedMesh(uint32_t vao_buffer_id, unsigned int numVertices,
                unsigned int numIndices)
    {
      vao_id = vao_buffer_id;
      NumVertices = numVertices;
      NumIndices = numIndices;
    }
  };

} // namespace Component
