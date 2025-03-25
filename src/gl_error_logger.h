#pragma once

namespace ErrorLogger
{
	void SetupErrorMessageCallback();
	void OnDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

	void LogGlError();
}
