#pragma once

#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/vector_float3.hpp"
#include "scene/camera/camera.h"
namespace Camera {

class Orbit : public Camera::Camera {
private:
  float angle = 0;
  glm::vec3 m_position = glm::vec3(0, 0, 10);

public:
  Orbit() = default;
  glm::mat4 get_view_matrix();
  glm::mat4 update();
  ~Orbit();
};
} // namespace Camera
