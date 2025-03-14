#pragma once
#include "entt.hpp"
#include "scene/camera/camera.h"
#include "shaders/uniform_buffer.h"
#include "systems/render.h"

class Scene
{
private:
  entt::registry m_registry;
  System::Render m_render_system;
  Shader::UniformBuffer m_uniform_buffer;

  glm::mat4x4 m_camera;
  void setup_entities();

public:
  void render();
  void init();
  ~Scene();
};
