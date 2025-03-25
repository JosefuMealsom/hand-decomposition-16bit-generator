// GLFW manages interating with the system in regards to input,
// creating a window, and to be able to render to the screen.

// GLAD manages function pointers for opengl. Opengl is open so its
// up to the device manufacturer to implement the specification, and there
// is no defined way of knowing where those functions exist at compile time.
// So GLAD handles getting those functions at runtime. These functions are
// actually IN the graphics drivers.
#include "pch/pch.h"

#include "logger.h"
#include "window.h"

static void framebuffer_size_callback(GLFWwindow* w, int width, int height)
{
	LOG_INFO("Resized window, {0} {1}", width, height);

	// This takes into the account of the dpi
	int framebuffer_width, framebuffer_height;
	glfwGetFramebufferSize(w, &framebuffer_width, &framebuffer_height);
	glViewport(0, 0, framebuffer_width, framebuffer_height);
}

GLFWwindow* Window::create_window(int width, int height, const char* title)
{
	int a = glfwInit();
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
	// This is required for mac
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
	glfwMakeContextCurrent(window);
	// This disables vsync
	glfwSwapInterval(0);

	if (window == NULL)
	{
		LOG_ERROR("Failed to create GLFW window");
		glfwTerminate();

		return nullptr;
	}

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		LOG_ERROR("Failed to initialize GLAD");
		// need to figure out NULL vs nullptr
		return nullptr;
	}

	// This could be defined smaller than the window if you want.
	// Other content could be displayed around the opengl rendering
	// context.
	// Behind the scenes it normalises the coordinates to NDC, between -1 and 1
	// and can then convert them to the screen coordinates.
	// Doesn't affect glClear
	// https://stackoverflow.com/questions/18830589/shouldnt-glclearcolor-obey-the-drawing-area-set-by-glviewport
	glViewport(0, 0, width, height);

	LOG_INFO("Initialised window");

	glfwSetWindowSizeCallback(window, *framebuffer_size_callback);

	framebuffer_size_callback(window, width, height);
	return window;
}
