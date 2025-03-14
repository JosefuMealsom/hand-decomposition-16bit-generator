#define STB_IMAGE_IMPLEMENTATION
#include "pch/pch.h"
#include <stb_image.h>

#include "shaders/texture_loader.h"

uint32_t Shader::TextureLoader::load_texture(const std::string &texture_path,
                                             uint32_t width, uint32_t height,
                                             uint32_t num_channels) {
  uint32_t texture_id;
  // setup textures
  glGenTextures(1, &texture_id);
  glBindTexture(GL_TEXTURE_2D, texture_id);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
  // This is when the texture is far away.
  // GL_NEAREST is the default filtering option. It will take the closest pixel
  // as a result of the interpolation. Good for pixelated look.
  // GL_LINEAR will interpolate between those pixels, and will make it smoother;
  // potentially blurry. Also known as bilinear filtering. Linear is good for
  // magnifying operations. GL_NEAREST_MIPMAP_NEAREST, takes the nearest mip map
  // and samples the nearest pixel as a result of that interpolation.
  // GL_LINEAR_MIPMAP_NEAREST, takes the nearest mip map and linearly
  // interpolates in that texture. GL_NEAREST_MIPMAP_LINEAR, linear interpolate
  // between the mip maps and get the nearest pixel of the interpolated texture.
  // GL_LINEAR_MIPMAP_LINEAR linear interpolate both the mip maps and the
  // texture lookup. as a result of that interpolation.
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  // This is the magnification filter (whe/Users/Joe/Downloads/wood-grain-texture.jpg n the texture is super close).
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // Pretty anal, but these params should be unsigned,
  // and the function only accepts ints.
  int w = (int)width;
  int h = (int)height;
  int channels = (int)num_channels;

  unsigned char *data = stbi_load(texture_path.c_str(), &w, &h, &channels, 0);

  // 1. Type of texture.
  // 2. Mip map level, if you want to define your own mip maps. 0 is base, but
  // I will just use the built in functionality to generate them.
  // 3. What format to store the texture.
  // 4/5. width and height.
  // 6. Should always be 0; it's legacy stuff.
  // 7/8. format and datatype of the image.
  // 9. The data.
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE,
               data);
  // It doesn't make sense to use high resolution textures for far away objects,
  // and also it's difficult for opengl to determine which fragment to use on
  // high resolution textures when they are so far away which creates artifacts.
  glGenerateMipmap(GL_TEXTURE_2D);

  glBindTexture(GL_TEXTURE_2D, 0);

  return texture_id;
}
