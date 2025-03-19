#include "pch/pch.h"

#include "scene/scene.h"
#include "window.h"

#include "logger.h"

int main()
{
  Log::init();

  GLFWwindow *window = Window::create_window(1920, 1080, "My window");

  if (window == nullptr)
  {
    return -1;
  }

  Scene scene = Scene();

  while (!glfwWindowShouldClose(window) && !scene.shouldQuitApplication())
  {
    scene.Render();
    // We have a double buffer(colour buffers) that contain all the
    // pixels, don't want a single buffer as takes time to draw the pixels.
    // This would mean that there is a flicker as the pixels are drawn.
    // Thats why we draw to a back buffer and then swap them.
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  LOG_INFO("Closing application");
  glfwTerminate();
  return 0;
}
