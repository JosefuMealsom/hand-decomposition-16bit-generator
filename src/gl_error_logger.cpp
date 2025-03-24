#include "gl_error_logger.h"
#include "logger.h"

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
