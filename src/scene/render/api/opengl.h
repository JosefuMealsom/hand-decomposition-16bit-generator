#pragma once
#include "glm/ext/vector_float3.hpp"
#include "scene/render/api/renderer_api.h"
#include <glm/vec3.hpp>

class OpenGLRendererApi : public RendererAPI {
private:
  glm::vec3 m_clear_color = {0, 0, 0};

public:
  OpenGLRendererApi();
  void draw_mesh() override;
  void set_clear_colour(const glm::vec3 &color) override;
  void clear() override;
};
