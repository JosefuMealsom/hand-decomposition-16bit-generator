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
#include "shaders/glsl/basic/uv_material.h"
#include "shaders/uniform_buffer.h"

#include "file_system/file_writer.h"
#include "render/image_writer.h"
#include "mesh/loader.h"
#include "scene/render/fbo/bit_depth_16.h"
#include "scene/render/fbo/msaa_fbo.h"
#include "feature_flags.h"
#include "gl_error_logger.h"

#define WIDTH 3840
#define HEIGHT 2160

Scene::Scene()
{
	SetupEntities();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_DEBUG_OUTPUT);

	ErrorLogger::SetupErrorMessageCallback();

	m_render_system = System::Render();
	m_uniform_buffer = Shader::UniformBuffer();
	m_fbo = new Render::FBO::BitDepth16(WIDTH, HEIGHT);
	m_msaaFbo = new Render::FBO::MSAA(WIDTH, HEIGHT);

	glm::vec3 cPosition = glm::vec3(0., 0., 1000.);
	glm::vec3 cFront = glm::vec3(0., 0., -1.);
	glm::vec3 cUp = glm::vec3(0., 1., 0.);

	m_uniform_buffer.update_camera(glm::lookAt(cPosition, cFront, cUp));
	m_uniform_buffer.update_projection(glm::ortho(-960., 960., 540., -540., 0., 10000.));
}

void Scene::SetupEntities()
{
	auto uvEntity = m_registry_uvs.create();

	std::string path = "./hand-updated-2.fbx";
	Component::IndexedMesh mesh = Mesh::Loader::LoadMeshFromFile(path);

	std::shared_ptr<Shader::Program> basic_shader =
		std::make_shared<Shader::BasicMaterial>(glm::vec3(1.f, 1.f, 1.f));

	Component::Material material(basic_shader);

	m_registry_hand_silhouette.emplace<Component::IndexedMesh>(uvEntity, mesh);
	m_registry_hand_silhouette.emplace<Component::Material>(uvEntity, material);

	auto silhouetteEntity = m_registry_hand_silhouette.create();
	std::shared_ptr<Shader::Program> uvsShader =
		std::make_shared<Shader::UVMaterial>();

	Component::Material uvMaterial(uvsShader);
	m_registry_uvs.emplace<Component::IndexedMesh>(silhouetteEntity, mesh);
	m_registry_uvs.emplace<Component::Material>(silhouetteEntity, uvMaterial);
};

void Scene::DrawScene(entt::registry& registry)
{
	glClearColor(0.f, 0.f, 0.f, 0.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_render_system.render(registry);
}

void Scene::Render()
{
	glViewport(0, 0, WIDTH, HEIGHT);

	// Render hand silhouette
	m_msaaFbo->bind();
	DrawScene(m_registry_hand_silhouette);

	glBindFramebuffer(GL_READ_FRAMEBUFFER, m_msaaFbo->id());
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo->id());

	glBlitFramebuffer(0, 0, WIDTH, HEIGHT, 0, 0, WIDTH, HEIGHT, GL_COLOR_BUFFER_BIT, GL_NEAREST);

	glBindFramebuffer(GL_READ_FRAMEBUFFER, m_fbo->id());
	Render::Image::Write16BitBufferToRawFile(WIDTH, HEIGHT, "./output/hand_silhouette.raw");

	m_fbo->bind();

	glViewport(0, 0, WIDTH, HEIGHT);

	DrawScene(m_registry_uvs);
	Render::Image::Write16BitBufferToRawFile(WIDTH, HEIGHT, "./output/hand_uvs.raw");

	DrawScene(m_registry_hand_silhouette);
	m_fbo->unbind();

	m_shouldQuitApplication = true;
};

Scene::~Scene()
{
	delete m_fbo;
	delete m_msaaFbo;
}
