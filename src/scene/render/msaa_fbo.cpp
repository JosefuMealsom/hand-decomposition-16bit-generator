#include "msaa_fbo.h"
#include "pch/pch.h"
#include <glad/glad.h>
#include "shaders/texture_16bit_generator.h"
#include "logger.h"
#include "gl_error_logger.h"

// Requires OpenGL 4.3 and above therefore cannot be used on Macs.
Render::MSAAFbo::MSAAFbo(unsigned int w, unsigned int h)
{
  m_fboTex = Texture::generate16bitTexture(w, h);
  glGenFramebuffers(1, &m_framebuffer);
  glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);

  glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_fboTex);
  glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGBA16, w, h, GL_TRUE);
  glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);

  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, m_fboTex, 0);

  glGenRenderbuffers(1, &m_rbo);
  glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
  glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH24_STENCIL8, w, h);
  glBindRenderbuffer(GL_RENDERBUFFER, 0);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);

  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
  {
    LOG_ERROR("Framebuffer is not complete!");
    ErrorLogger::LogGlError();
  }

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Render::MSAAFbo::bind()
{
  glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
}

void Render::MSAAFbo::unbind()
{
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
