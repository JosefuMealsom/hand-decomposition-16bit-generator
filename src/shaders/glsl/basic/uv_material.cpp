#include "pch/pch.h"
#include "shaders/glsl/basic/uv_material.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float3.hpp"
#include "shaders/texture_16bit_generator.h"
#include "shaders/texture_loader.h"
#include "logger.h"
#include "shaders/texture_loader.h"

Shader::UVMaterial::UVMaterial()
	: Program(SourcePath("resources/shaders/vertex.glsl",
		"resources/shaders/uv_fragment.glsl"))
{
	init_shader_program();
}

void Shader::UVMaterial::init_shader_program()
{
	m_texture_id = Texture::generate16bitTexture(1920, 1080);

	bind();
	update_uniform_mat4("model", get_transform());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture_id);

	update_uniform_1i("texture1", 0);

	unbind();
}

glm::mat4 Shader::UVMaterial::get_transform()
{
	glm::mat4 transform = glm::mat4(1.0f);
	const float s = 40.;
	transform = glm::scale(transform, glm::vec3(-1., -1., 1.));
	transform = glm::translate(transform, glm::vec3(0, -100, 0));
	transform = glm::scale(transform, glm::vec3(s, s, s));
	transform = glm::rotate(transform, glm::radians(90.f),
		glm::vec3(1.0, 0.0, 0.0));
	transform = glm::rotate(transform, glm::radians(180.f),
		glm::vec3(0.0, 0.0, 1.0));

	return transform;
}

void Shader::UVMaterial::update()
{
	update_uniform_mat4("model", get_transform());
}
