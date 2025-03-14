#pragma once

#include "pch/pch.h"
#include <glm/vec3.hpp>

namespace Component {

struct IndexedMesh {
  uint32_t vao_id;
  std::vector<glm::vec3> vertices;
  std::vector<uint32_t> indices;

  IndexedMesh(uint32_t vao_buffer_id, const std::vector<glm::vec3> &verts,
              const std::vector<uint32_t> &inds) {
    vao_id = vao_buffer_id;
    vertices = verts;
    indices = inds;
  }

  uint32_t num_vertices() const { return vertices.size(); }
  uint32_t num_indices() const { return indices.size(); }
};

} // namespace Component
