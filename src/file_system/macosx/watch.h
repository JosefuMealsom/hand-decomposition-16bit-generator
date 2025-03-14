#pragma once
#include <CoreServices/CoreServices.h>

namespace FileSystem {
class Watch {
public:
  void register_on_save_callback(const char *);
  ~Watch();
};
} // namespace FileSystem
