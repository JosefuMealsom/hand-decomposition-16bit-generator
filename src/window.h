#pragma once

#include "pch/pch.h"

#define WINDOW_ON_RESIZE_FUNCTION GLFWwindow, int, int

namespace Window
{
  GLFWwindow *create_window(int, int, const char *);
}
