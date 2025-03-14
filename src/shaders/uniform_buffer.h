#pragma once

#include "glm/ext/matrix_float4x4.hpp"
#include "pch/pch.h"

namespace Shader
{

  class UniformBuffer
  {
  private:
    uint32_t m_id = 0;

  public:
    ~UniformBuffer();
    UniformBuffer();
    uint32_t get_id() const { return m_id; }
    void update_projection(const glm::mat4 &);
    void update_camera(const glm::mat4 &);
  };
} // namespace Shader
