#include "triangle.h"
#include "pch/pch.h"

namespace Mesh
{

  Component::IndexedMesh Triangle::generate_mesh()
  {
    float vertices[9] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};
    int inds[3] = {0, 1, 2};

    uint32_t vbo;
    uint32_t vao;
    uint32_t ebo;
    // Want to generate a buffer to store vertices to send to the GPU.
    // This is more efficient than sending them 1 by 1.
    // The size generates a number of buffers I think, or does it just affect the
    // id?
    glGenBuffers(1, &vbo);

    // Vertex array objects are required to draw anything in Opengl core,
    // otherwise nothing will be rendered!
    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // The static draw just indicates that the buffer isn't going to be changing.
    // If vertices change often then we would set it to dynamic draw.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &ebo);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(inds), inds, GL_STATIC_DRAW);
    // This unbinds the buffer so that any additional operations
    // don't affect the state machine. Actually probably don't need to do
    // this.
    /* glBindBuffer(GL_ARRAY_BUFFER, 0); */

    // 1. First param tells us what attribute to configure. In the shader
    // file this is marked with layout = 0.
    // 2. Next is the size of this attribute. We use 3 here as it is Vec3.
    // 3. This is the type
    // 4. This controls whether the data is normalised or not.
    // 5. This is the amount of memory consumed. This is the stride. Tells
    // us the memory between vertices, or the group of attributes assigned
    // to each vertex (normal, position, uvs). Also need to know whether
    // the data is tightly packed or not, ie there is no space in between
    // the attributes. A value of 0 works as well and tells opengl that
    // the data is tightly packed. When we have more attributes, we need
    // to be more careful about this.
    // 6. This is the offset of where the position data starts in the
    // buffer. If we have more attributes, then we need to offset this
    // pointer by the number of bytes.
    //

    // Also the vertex attributes take its data from data managed by
    // the vbo.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    // This enables the attributes as they are disabled by default. We pass in the
    // verte attribute location as the argument.
    glEnableVertexAttribArray(0);

    std::vector<glm::vec3> verts =
        std::vector<glm::vec3>(std::begin(vertices), std::end(vertices));
    std::vector<uint32_t> indices =
        std::vector<uint32_t>(std::begin(inds), std::end(inds));

    return Component::IndexedMesh(vao, verts.size(), indices.size());
  }

} // namespace Primitives
