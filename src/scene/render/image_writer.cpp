#include "pch/pch.h"
#include "image_writer.h"
#include <glad/glad.h>
#include "file_system/file_writer.h"
#include <assert.h>
#include <logger.h>
#include <fstream>
#include <iostream>

void Render::Image::WritePixelsToFile(unsigned int w, unsigned int h)
{
  unsigned short *pixels = new unsigned short[w * h * 4];
  glReadPixels(0, 0, w, h, GL_RGBA, GL_UNSIGNED_SHORT, pixels);

  std::ofstream myfile;
  myfile.open("pixels.txt");

  for (int x = 0; x < w; x++)
  {
    for (int y = 0; y < h; y++)
    {
      int i = y * w * 4 + x * 4;
      myfile << y << " " << x << " " << pixels[i] << " " << pixels[i + 1] << std::endl;
    }
  }

  myfile.close();
}

void Render::Image::PrintPixels(unsigned int w, unsigned int h)
{
  unsigned short *pixels = new unsigned short[w * h * 4];
  glReadPixels(0, 0, w, h, GL_RGBA, GL_UNSIGNED_SHORT, pixels);

  for (int x = 0; x < w; x++)
  {
    for (int y = 0; y < h; y++)
    {
      int i = y * w * 4 + x * 4;
      LOG_INFO("{} {}", pixels[i], pixels[i + 1]);
    }
  }
}

void Render::Image::Write8BitBufferToRawFile(unsigned int w, unsigned int h)
{
  unsigned short *pixels = new unsigned short[w * h * 4];
  glReadPixels(0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

  FileSystem::WriteBinaryFile("./test.raw", pixels, w * h * 4);

  delete[] pixels;
}

void Render::Image::Write16BitBufferToRawFile(unsigned int w, unsigned int h, const std::string &filename)
{
  unsigned short *pixels = new unsigned short[w * h * 4];
  glReadPixels(0, 0, w, h, GL_RGBA, GL_UNSIGNED_SHORT, pixels);

  FileSystem::WriteBinaryFile(filename, pixels, w * h * 4 * 2);

  delete[] pixels;
}
