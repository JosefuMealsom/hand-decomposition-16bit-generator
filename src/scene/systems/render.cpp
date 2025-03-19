#include "pch/pch.h"

#include "entt.hpp"
#include "render.h"

namespace System
{
  void Render::render(entt::registry &registry)
  {
    // what is the type here?
    auto renderable_entities =
        registry.view<Component::IndexedMesh, Component::Material>();

    for (entt::entity entity : renderable_entities)
    {
      Component::IndexedMesh &mesh =
          renderable_entities.get<Component::IndexedMesh>(entity);
      Component::Material &material =
          renderable_entities.get<Component::Material>(entity);

      material.shader->bind();

      material.shader->update();

      glBindVertexArray(mesh.vao_id);
      glDrawElements(GL_TRIANGLES, mesh.NumIndices, GL_UNSIGNED_INT, 0);

      material.shader->unbind();
    }
  }
} // namespace System
