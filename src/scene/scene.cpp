#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float3.hpp"
#include "logger.h"
#include "pch/pch.h"

#include "primitives/square.h"
#include "scene/components/components.h"
#include "scene/scene.h"
#include "scene/systems/render.h"
#include "shaders/glsl/basic/basic_material.h"
#include "shaders/uniform_buffer.h"

#include "shaders/texture_16bit_generator.h"
#include "file_system/file_writer.h"

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

	m_fboTex = Texture::generate16bitTexture(1920, 1080);
	glGenFramebuffers(1, &m_framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);

	//m_fboTex = Texture::generateEmpty16bitTexture(512, 512);

	glBindTexture(GL_TEXTURE_2D, m_fboTex);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_fboTex, 0);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cerr << "Framebuffer is not complete!" << std::endl;
	}

	//glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glGenRenderbuffers(1, &m_rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1920, 1080);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);
};

void Scene::renderToFramebuffer(int framebuffer)
{

	m_render_system.render(m_registry);

	int w = 1920;
	int h = 1080;

	unsigned short* pixels = new unsigned short[w * h * 4];
	glReadPixels(0, 0, w, h, GL_RGBA, GL_UNSIGNED_SHORT, pixels);

	//for (int x = 0; x < w; x++)
	//{
	//	for (int y = 0; y < h; y++)
	//	{
	//		int i = y * w * 4 + x * 4;
	//		std::cout << pixels[i] << " " << pixels[i + 1] << std::endl;
	//	}
	//}

	//FileSystem::WriteBinaryFile("C:\\Users\\dmshost\\Documents\\test.raw", pixels, w * h * 4 * 2);
	//int t = 40000;

	//std::cout << pixels[t] << " " << pixels[t + 1] << " " << pixels[t + 2] << " " << pixels[t + 3] << std::endl;
	//delete[] pixels;
}

void Scene::render()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);
	renderToFramebuffer(0);

	//glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
	//glClearColor(0.f, 0.f, 0.f, 1.f);
	//glClear(GL_COLOR_BUFFER_BIT);
	//renderToFramebuffer(0);
};

Scene::~Scene()
{
}
