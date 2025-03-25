#include "gl_error_logger.h"
#include "logger.h"
#include <glad/glad.h>

void ErrorLogger::SetupErrorMessageCallback()
{
	glDebugMessageCallback(&OnDebugCallback, nullptr);
}

void ErrorLogger::OnDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	LOG_ERROR(message);
}

void ErrorLogger::LogGlError()
{
	auto error = glGetError();

	if (error == 0)
	{
		return;
	}

	switch (error)
	{
	case 0x0502:
		LOG_ERROR("GL error 0x0502: Invalid operation");
		break;
	default:
		LOG_ERROR("GL error {}", error);
		break;
	}
}
