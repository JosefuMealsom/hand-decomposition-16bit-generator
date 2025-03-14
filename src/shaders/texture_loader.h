#pragma once
// Remove these pch definitions from the headers! Very bad
#include "pch/pch.h"

namespace Shader
{
  class TextureLoader
  {
  public:
    static uint32_t load_texture(const std::string &texture_path, uint32_t width,
                                 uint32_t height, uint32_t num_channels);
  };
}; // namespace Shader
