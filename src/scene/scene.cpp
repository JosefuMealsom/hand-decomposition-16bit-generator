#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float3.hpp"
#include "logger.h"
#include "pch/pch.h"

#include "primitives/square.h"
#include "scene/camera/orbit.h"
#include "scene/components/components.h"
#include "scene/scene.h"
#include "scene/systems/render.h"
#include "shaders/glsl/basic/basic_material.h"
#include "shaders/uniform_buffer.h"

#include "events/event_dispatcher.h"
#include "events/key_events.h"

void Scene::init()
{
  setup_entities();

  glEnable(GL_DEPTH_TEST);

  m_render_system = System::Render();
  m_uniform_buffer = Shader::UniformBuffer();

  glm::vec3 cPosition = glm::vec3(0., 0., 1.);
  glm::vec3 cFront = glm::vec3(0., 0., -1.);
  glm::vec3 cUp = glm::vec3(0., 1., 0.);

  m_uniform_buffer.update_camera(glm::lookAt(cPosition, cFront, cUp));
  m_uniform_buffer.update_projection(glm::ortho(-1., 1., 1., -1., 0., 1000.));
}

void Scene::setup_entities()
{
  auto entity = m_registry.create();

  Component::IndexedMesh mesh = Primitives::Square::generate_square_mesh();

  std::shared_ptr<Shader::Program> basic_shader =
      std::make_shared<Shader::BasicMaterial>(glm::vec3(1.f, 1.f, 1.f));

  Component::Material material(basic_shader);

  m_registry.emplace<Component::IndexedMesh>(entity, mesh);
  m_registry.emplace<Component::Material>(entity, material);
};

void Scene::render()
{
  glClearColor(0.f, 0.f, 0.f, 1.f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  m_render_system.render(m_registry);
};

Scene::~Scene()
{ /* delete m_camera; */
}
