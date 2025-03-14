#pragma once

#include "glm/ext/matrix_float4x4.hpp"
#include "pch/pch.h"
#include "shaders/program.h"
#include <cstdint>

namespace Shader
{

  class BasicMaterial : public Program
  {
  private:
    glm::vec3 m_color;
    float m_rotation = 0;
    uint32_t m_texture_id;
    void init_shader_program();
    glm::mat4 get_transform();

  public:
    BasicMaterial(glm::vec3 color);
    void update() override;
  };

}
