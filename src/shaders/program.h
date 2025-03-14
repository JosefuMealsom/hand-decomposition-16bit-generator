#pragma once

#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>

namespace Shader {

struct SourcePath {
  std::string vertex_shader;
  std::string fragment_shader;

  SourcePath(const std::string &vertex_source,
             const std::string &fragment_source)
      : vertex_shader(vertex_source), fragment_shader(fragment_source) {}

  SourcePath(const SourcePath &other) {
    vertex_shader = other.vertex_shader;
    fragment_shader = other.fragment_shader;
  }
};

class Program {
private:
  uint32_t m_program_id;
  std::unordered_map<std::string, int> m_uniform_location_cache;
  SourcePath m_source_path;
  uint32_t get_uniform_location(const std::string name);

public:
  Program(const SourcePath &source_path);
  ~Program();

  void update_uniform_1f(const std::string &name, float);
  void update_uniform_2f(const std::string &name, const glm::vec2 &);
  void update_uniform_3f(const std::string &name, const glm::vec3 &);
  void update_uniform_4f(const std::string &name, const glm::vec4 &);

  void update_uniform_1i(const std::string &name, int);

  void update_uniform_mat3(const std::string &name, const glm::mat3 &);
  void update_uniform_mat4(const std::string &name, const glm::mat4 &);

  void bind();
  void unbind();

  virtual void update(){};
};
} // namespace Shader
