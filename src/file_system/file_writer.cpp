#include "file_system/file_writer.h"
#include <string>
#include <fstream>
#include <iostream>

void FileSystem::WriteBinaryFile(std::string path, void *data, unsigned int numBytes)
{
  std::ofstream fs(path, std::ios::out | std::ios::binary);
  fs.write(reinterpret_cast<const char *>(data), numBytes);
  fs.close();
}
