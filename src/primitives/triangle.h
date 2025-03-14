#pragma once

#include "scene/components/components.h"

namespace Primitives {

class Triangle {
public:
  static Component::IndexedMesh generate_mesh();
};
} // namespace Primitives
