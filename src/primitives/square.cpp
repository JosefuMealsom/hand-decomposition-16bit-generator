#include "pch/pch.h"

#include "scene/components/components.h"
#include "square.h"
#include <cstdint>

namespace Primitives
{
  // For uvs think of a graph axes to know how the lookup works eg top right is
  // 1, 1.
  static float verts[] = {
      1.f, 1.f, 0.0f, 1.0f, 1.0f,   // top right
      1.f, -1.f, 0.0f, 1.0f, 0.0f,  // bottom right
      -1.f, -1.f, 0.0f, 0.0f, 0.0f, // bottom left
      -1.f, 1.f, 0.0f, 0.0f, 1.0f,  // top left
  };

  uint32_t inds[] = {0, 1, 3, 1, 2, 3};

  // How does the initialisation work here?
  static const std::vector<glm::vec3> vertices(std::begin(verts),
                                               std::end(verts));
  static const std::vector<uint32_t> indices(std::begin(inds), std::end(inds));

  Component::IndexedMesh Square::generate_square_mesh()
  {
    uint32_t vbo_id;
    uint32_t vao_id;
    uint32_t ebo_id;

    glGenBuffers(1, &vbo_id);
    glGenVertexArrays(1, &vao_id);

    glBindVertexArray(vao_id);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
    // This is used when we want to reuse vertices, we just give the
    // indices of the that are shared so we can draw 2 triangles.
    // This also gets bound to the VAO object.
    glGenBuffers(1, &ebo_id);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(inds), inds, GL_STATIC_DRAW);

    // Note that there is a maximum number of attributes you
    // can define. Minimum is usually 16.

    uint32_t stride = 5 * sizeof(float);

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, 0);
    glEnableVertexAttribArray(0);

    // UVs
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride,
                          (void *)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);

    return Component::IndexedMesh(vao_id, vertices, indices);
  }

} // namespace Primitives
