#pragma once

#include "scene/components/components.h"

namespace Mesh
{

  class Triangle
  {
  public:
    static Component::IndexedMesh generate_mesh();
  };
} // namespace Primitives
