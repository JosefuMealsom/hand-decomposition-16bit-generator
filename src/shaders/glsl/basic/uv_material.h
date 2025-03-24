#pragma once

#include "glm/ext/matrix_float4x4.hpp"
#include "shaders/program.h"
#include <cstdint>

namespace Shader
{
  class UVMaterial : public Program
  {
  private:
    uint32_t m_texture_id;
    void init_shader_program();
    glm::mat4 get_transform();

  public:
    UVMaterial();
    void update() override;
  };

}
