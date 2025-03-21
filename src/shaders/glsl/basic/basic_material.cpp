#include "shaders/glsl/basic/basic_material.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float3.hpp"
#include "pch/pch.h"
#include "shaders/texture_16bit_generator.h"
#include "shaders/texture_loader.h"
#include "logger.h"
#include "shaders/texture_loader.h"

Shader::BasicMaterial::BasicMaterial(glm::vec3 color)
    : Program(SourcePath("resources/shaders/vertex.glsl",
                         "resources/shaders/fragment.glsl"))
{
  m_color = color;
  init_shader_program();
}

void Shader::BasicMaterial::init_shader_program()
{

  m_texture_id = Texture::generate16bitTexture(1920, 1080);
  // m_texture_id = Texture::generate8bitTexture();

  // m_texture_id = TextureLoader::load_texture("./resources/images/texture-blender.png", 1024, 1024, 4);

  bind();
  update_uniform_mat4("model", get_transform());

  // Only need to bind this texture once, which is great.
  // Also, if we want to bin more textures, need to set the active
  // texture units to increment, so next will be GL_TEXTURE1. These
  // appear as uniforms in our program.
  // We also need to get the uniform locations of the samplers and set them.
  // So glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0).
  // Using just one texture will work without this though.
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, m_texture_id);

  update_uniform_1i("texture1", 0);

  unbind();
}

glm::mat4 Shader::BasicMaterial::get_transform()
{
  glm::mat4 transform = glm::mat4(1.0f);
  const float s = 40.;
  transform = glm::scale(transform, glm::vec3(1., -1., 1.));
  transform = glm::translate(transform, glm::vec3(0, -100, 0));
  transform = glm::scale(transform, glm::vec3(s, s, s));
  transform = glm::rotate(transform, glm::radians(90.f),
                          glm::vec3(1.0, 0.0, 0.0));
  transform = glm::rotate(transform, glm::radians(180.f),
                          glm::vec3(0.0, 0.0, 1.0));

  return transform;
}

void Shader::BasicMaterial::update()
{
  update_uniform_mat4("model", get_transform());
}
