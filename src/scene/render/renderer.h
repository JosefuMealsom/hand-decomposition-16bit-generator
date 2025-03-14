#pragma once
#include "scene/render/api/renderer_api.h"
#include <glm/vec3.hpp>

// This is a static class that submits calls to the renderer
// backend via the render command class. The render command class
// holds a static reference to an api class that implements the functionality.
// In our case; an opengl_api renderer.
// Can be also super fun to implement the same for a metal renderer.
class Renderer {
private:
  static RenderAPIEnum s_api;

public:
  void begin_scene();
  void end_scene();

  void draw_object();
};
