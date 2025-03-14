#pragma once
#include <glm/vec3.hpp>

enum class RenderAPIEnum { OpenGL = 0, Metal = 1 };

// Derived classes will need to implement a queue that
// organises how the render operations happen. This is so that
// it can be optimised, for instance, rendering all the meshes that
// share a shader at the same time as switching shaders is expensive.
class RendererAPI {
private:
  static RenderAPIEnum s_api;

public:
  virtual void draw_mesh() = 0;
  virtual void set_clear_colour(const glm::vec3 &color) = 0;
  virtual void clear() = 0;

  inline static RenderAPIEnum get_api() { return s_api; }
};
