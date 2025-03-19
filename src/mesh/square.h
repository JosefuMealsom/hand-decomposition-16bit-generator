#pragma once

#include "scene/components/components.h"
#include <glm/vec3.hpp>

namespace Mesh
{

  class Square
  {
  public:
    static Component::IndexedMesh generate_square_mesh();
  };
} // namespace Primitives
