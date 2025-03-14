#include "pch/pch.h"

#include "logger.h"
#include "shaders/compiler.h"
#include <fstream>

static std::string read_from_file(const std::string file_path) {
  std::ifstream input_file_stream;
  std::string output = "";

  // ensure ifstream objects can throw exceptions:
  input_file_stream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try {
    input_file_stream.open(file_path);
    std::stringstream file_string_stream;
    file_string_stream << input_file_stream.rdbuf();

    input_file_stream.close();

    output = file_string_stream.str();
  } catch (std::ifstream::failure e) {
    LOG_ERROR("Error reading from file {0}", file_path);
  }

  return output;
}

int Shader::Compiler::compile_shader(const std::string source_path,
                                     uint32_t shader_type) {
  uint32_t shader_id = 0;
  shader_id = glCreateShader(shader_type);

  std::string source_string = read_from_file(source_path);

  // Better way of doing this?
  if (source_string.length() == 0) {
    return 0;
  }

  // Why doesn't this work? Is it because the memory gets freed
  // after the function ends? I don't think so...
  /* const char *source = read_from_file(m_source_path).c_str(); */

  const char *char_source = source_string.c_str();
  glShaderSource(shader_id, 1, &char_source, NULL);
  glCompileShader(shader_id);

  int success;
  glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);

  if (!success) {
    char info_log[512];
    glGetShaderInfoLog(shader_id, 512, NULL, info_log);
    LOG_ERROR("Error compiling shader: {0}", info_log);
  }
  return shader_id;
}

int Shader::Compiler::compile_program(const std::string vertex_path,
                                      const std::string fragment_path) {
  uint32_t vertex_id = compile_shader(vertex_path, GL_VERTEX_SHADER);
  uint32_t fragment_id = compile_shader(fragment_path, GL_FRAGMENT_SHADER);

  int success;
  uint32_t program_id = glCreateProgram();
  glAttachShader(program_id, vertex_id);
  glAttachShader(program_id, fragment_id);

  glLinkProgram(program_id);
  glGetProgramiv(program_id, GL_LINK_STATUS, &success);

  if (!success) {
    char info_log[512];
    glGetProgramInfoLog(program_id, 512, NULL, info_log);
    LOG_ERROR("Error compiling shader program: {0}", info_log);
  }

  // delete the shaders as they're linked into our program now and no longer
  // necessary
  glDeleteShader(vertex_id);
  glDeleteShader(fragment_id);

  return program_id;
}
