#include "uniform_buffer.h"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/gtc/type_ptr.hpp"

Shader::UniformBuffer::UniformBuffer() {
  glGenBuffers(1, &m_id);

  glBindBuffer(GL_UNIFORM_BUFFER, m_id);
  glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
  glBindBuffer(GL_UNIFORM_BUFFER, 0);
  glBindBufferRange(GL_UNIFORM_BUFFER, 0, m_id, 0, 2 * sizeof(glm::mat4));
}

void Shader::UniformBuffer::update_projection(const glm::mat4 &projection) {
  glBindBuffer(GL_UNIFORM_BUFFER, m_id);
  glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4),
                  glm::value_ptr(projection));
  glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void Shader::UniformBuffer::update_camera(const glm::mat4 &camera) {
  glBindBuffer(GL_UNIFORM_BUFFER, m_id);
  glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4),
                  glm::value_ptr(camera));
  glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

Shader::UniformBuffer::~UniformBuffer() {}
