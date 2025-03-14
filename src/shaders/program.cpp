#include "pch/pch.h"

#include "logger.h"
#include "program.h"
#include "shaders/compiler.h"
#include <cstdint>
#include <glm/gtc/type_ptr.hpp>

namespace Shader {

Program::Program(const SourcePath &source_path) : m_source_path(source_path) {
  m_program_id = Compiler::compile_program(source_path.vertex_shader,
                                           source_path.fragment_shader);

  // Bind uniform buffer. Better place to put this?
  uint32_t matrices_uniform_index =
      glGetUniformBlockIndex(m_program_id, "Matrices");
  glUniformBlockBinding(m_program_id, matrices_uniform_index, 0);
}

Program::~Program() {
  LOG_INFO("Deleting shader {0}", m_program_id);
  glDeleteProgram(m_program_id);
}

void Program::update_uniform_1f(const std::string &name, float value) {
  glUniform1f(get_uniform_location(name), value);
};
void Program::update_uniform_2f(const std::string &name,
                                const glm::vec2 &value) {
  glUniform2f(get_uniform_location(name), value.x, value.y);
};
void Program::update_uniform_3f(const std::string &name,
                                const glm::vec3 &value) {
  glUniform3f(get_uniform_location(name), value.x, value.y, value.z);
};
void Program::update_uniform_4f(const std::string &name,
                                const glm::vec4 &value) {
  glUniform4f(get_uniform_location(name), value.x, value.y, value.z, value.w);
};

void Program::update_uniform_1i(const std::string &name, int value) {
  glUniform1i(get_uniform_location(name), value);
};

void Program::update_uniform_mat3(const std::string &name,
                                  const glm::mat3 &value) {
  glUniformMatrix3fv(get_uniform_location(name), 1, GL_FALSE,
                     glm::value_ptr(value));
};
void Program::update_uniform_mat4(const std::string &name,
                                  const glm::mat4 &value) {
  glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE,
                     glm::value_ptr(value));
};

void Program::bind() { glUseProgram(m_program_id); }

void Program::unbind() { glUseProgram(0); }

uint32_t Program::get_uniform_location(const std::string name) {
  if (m_uniform_location_cache[name]) {
    return m_uniform_location_cache[name];
  }
  int uniform_location = glGetUniformLocation(m_program_id, name.c_str());
  if (uniform_location == -1) {
    /* LOG_WARN("Uniform {0} not defined in shader program {1}", name, */
    /*          m_program_id); */
    return -1;
  }

  m_uniform_location_cache[name] = uniform_location;
  return uniform_location;
}

} // namespace Shader
