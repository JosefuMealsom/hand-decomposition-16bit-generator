#pragma once

namespace Render::FBO {
	class Base {
		virtual void bind() = 0;
		virtual void unbind() = 0;
	};
}
