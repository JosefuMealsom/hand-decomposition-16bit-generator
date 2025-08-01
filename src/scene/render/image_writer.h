#pragma once

#include <string>
namespace Render
{
  namespace Image
  {
    void PrintPixels(unsigned int w, unsigned int h);
    void WritePixelsToFile(unsigned int w, unsigned int h);
    void Write8BitBufferToRawFile(unsigned int w, unsigned int h, const std::string &filename);
    void Write16BitBufferToRawFile(unsigned int w, unsigned int h, const std::string &filename);
  }
}
