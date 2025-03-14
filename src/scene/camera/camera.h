#pragma once
#include "glm/ext/matrix_float4x4.hpp"

namespace Camera {

class Camera {
public:
  virtual glm::mat4 update() = 0;
};
} // namespace Camera
