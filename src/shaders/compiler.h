#pragma once
#include "pch/pch.h"

namespace Shader {
class Compiler {
private:
  static int compile_shader(std::string source_path, uint32_t shader_type);

public:
  static int compile_program(std::string vertex_path,
                             std::string fragment_path);
};
} // namespace Shader
