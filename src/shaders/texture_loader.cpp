#define STB_IMAGE_IMPLEMENTATION
#include "pch/pch.h"
#include <stb_image.h>

#include "shaders/texture_loader.h"

uint32_t Shader::TextureLoader::load_texture(const std::string &texture_path,
                                             uint32_t width, uint32_t height,
                                             uint32_t num_channels)
{
  uint32_t texture_id;

  glGenTextures(1, &texture_id);
  glBindTexture(GL_TEXTURE_2D, texture_id);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  int w = (int)width;
  int h = (int)height;
  int channels = (int)num_channels;

  unsigned char *data = stbi_load(texture_path.c_str(), &w, &h, &channels, 0);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);

  glBindTexture(GL_TEXTURE_2D, 0);

  return texture_id;
}
