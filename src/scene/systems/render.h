#pragma once
#include "entt.hpp"
#include "scene/components/components.h"

namespace System {
class Render {
public:
  void render(entt::registry &registry);
};

} // namespace System
