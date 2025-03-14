#include "orbit.h"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/trigonometric.hpp"

glm::mat4 Camera::Orbit::update()
{
  angle += 0.01;
  float y = 0;

  float radius = 5;

  float x = glm::cos(glm::radians(angle)) * radius;
  float z = glm::sin(glm::radians(angle)) * radius;
  return glm::lookAt(glm::vec3(0, 0, 10), glm::vec3(0, 0, 0),
                     glm::vec3(0, 1, 0));
}
