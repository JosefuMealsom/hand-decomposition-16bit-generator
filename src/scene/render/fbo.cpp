#include "fbo.h"
#include "pch/pch.h"
#include <glad/glad.h>
#include "shaders/texture_16bit_generator.h"

Render::Fbo::Fbo(unsigned int w, unsigned int h)
{
	m_fboTex = Texture::generateEmpty16bitTexture(w, h);
	glGenFramebuffers(1, &m_framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);

	glBindTexture(GL_TEXTURE_2D, m_fboTex);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_fboTex, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cerr << "Framebuffer is not complete!" << std::endl;
	}

	//glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glGenRenderbuffers(1, &m_rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, w, h);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);

}

void Render::Fbo::bind()
{
	glBindRenderbuffer(GL_RENDERBUFFER, m_framebuffer);
}

void Render::Fbo::unbind()
{
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}
