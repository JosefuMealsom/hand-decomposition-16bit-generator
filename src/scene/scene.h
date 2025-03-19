#pragma once
#include "entt.hpp"
#include "shaders/uniform_buffer.h"
#include "systems/render.h"
#include "render/fbo.h"

class Scene
{
private:
  entt::registry m_registry;
  System::Render m_render_system;
  Shader::UniformBuffer m_uniform_buffer;
  Render::Fbo m_fbo;

  void SetupEntities();
  void DrawScene();
  void PrintPixels(unsigned short *, unsigned int, unsigned int);
  bool m_shouldQuitApplication = false;

public:
  void Render();
  void Init();
  ~Scene();
  bool shouldQuitApplication() { return m_shouldQuitApplication; };
};
