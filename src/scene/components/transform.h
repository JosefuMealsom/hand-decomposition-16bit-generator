#pragma once

#include "glm/vec3.hpp"

namespace Component
{
  struct Transform
  {

    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    Transform() = default;
    Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
        : position(position), rotation(rotation), scale(scale) {};
  };
}
