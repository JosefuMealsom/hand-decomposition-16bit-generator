#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float3.hpp"
#include "logger.h"
#include "pch/pch.h"

#include "mesh/square.h"
#include "scene/components/components.h"
#include "scene/scene.h"
#include "scene/systems/render.h"
#include "shaders/glsl/basic/basic_material.h"
#include "shaders/uniform_buffer.h"

#include "file_system/file_writer.h"
#include "render/image_writer.h"
#include "mesh/loader.h"

Scene::Scene()
{
	SetupEntities();

	glEnable(GL_DEPTH_TEST);

	m_render_system = System::Render();
	m_uniform_buffer = Shader::UniformBuffer();
	m_fbo = new Render::Fbo(1920, 1080);

	glm::vec3 cPosition = glm::vec3(0., 0., 500.);
	glm::vec3 cFront = glm::vec3(0., 0., -1.);
	glm::vec3 cUp = glm::vec3(0., 1., 0.);

	m_uniform_buffer.update_camera(glm::lookAt(cPosition, cFront, cUp));
	m_uniform_buffer.update_projection(glm::ortho(-960., 960., 540., -540., 0., 1000.));
}

void Scene::SetupEntities()
{
	auto entity = m_registry.create();

	std::string path = "./resources/models/testy.fbx";
	Component::IndexedMesh mesh = Mesh::Loader::LoadMeshFromFile(path);

	std::shared_ptr<Shader::Program> basic_shader =
		std::make_shared<Shader::BasicMaterial>(glm::vec3(1.f, 1.f, 1.f));

	Component::Material material(basic_shader);

	m_registry.emplace<Component::IndexedMesh>(entity, mesh);
	m_registry.emplace<Component::Material>(entity, material);
};

void Scene::DrawScene()
{
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_render_system.render(m_registry);
}

void Scene::Render()
{
	DrawScene();

	// m_fbo->bind();

	// DrawScene();
	// Render::Image::PrintPixels(1920, 1080);
	// Render::Image::Write16BitBufferToRawFile(1920, 1080);
	// m_fbo->unbind();

	// m_shouldQuitApplication = true;
};

Scene::~Scene()
{
	delete m_fbo;
}
