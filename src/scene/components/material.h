#pragma once
#include "shaders/program.h"
#include <glm/mat4x4.hpp>

namespace Component
{
  struct Material
  {

    const std::shared_ptr<Shader::Program> shader;

    Material(const std::shared_ptr<Shader::Program> &_shader) : shader(_shader) {}
  };

}
