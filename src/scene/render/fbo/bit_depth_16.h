#pragma once
#include "scene/render/fbo/base_fbo.h"

namespace Render::FBO
{
	class BitDepth16 : public Base
	{
	public:
		BitDepth16(unsigned int w, unsigned int h);
		void bind() override;
		void unbind() override;
		inline unsigned int id() const { return m_framebuffer; }

	private:
		unsigned int m_framebuffer;
		unsigned int m_fboTex;
		unsigned int m_rbo;
	};
}
