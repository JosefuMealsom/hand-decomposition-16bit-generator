#pragma once
#include "entt.hpp"
#include "shaders/uniform_buffer.h"
#include "systems/render.h"
//#include "render/bit.h"

namespace Render::FBO
{
	class BitDepth16;
	class MSAA;
}
class Scene
{
public:
	void Render();
	Scene();
	~Scene();
	bool shouldQuitApplication() { return m_shouldQuitApplication; };

private:
	entt::registry m_registry_uvs;
	entt::registry m_registry_hand_silhouette;
	System::Render m_render_system;
	Shader::UniformBuffer m_uniform_buffer;
	Render::FBO::BitDepth16* m_fbo;
	Render::FBO::MSAA* m_msaaFbo;

	void SetupEntities();
	void DrawScene(entt::registry&);
	bool m_shouldQuitApplication = false;
};
