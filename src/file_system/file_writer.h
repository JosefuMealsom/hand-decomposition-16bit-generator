#pragma once
#include <string>

namespace FileSystem
{
  void WriteBinaryFile(const std::string &path, void *data, unsigned int numBytes);
}
