#include "opengl.h"
#include "logger.h"

OpenGLRendererApi::OpenGLRendererApi() {}

void OpenGLRendererApi::draw_mesh() { LOG_INFO("DRAW MESH"); }

void OpenGLRendererApi::set_clear_colour(const glm::vec3 &color) {
  m_clear_color = color;
}

void OpenGLRendererApi::clear() {
  glClearColor(m_clear_color.r, m_clear_color.g, m_clear_color.b, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
};
