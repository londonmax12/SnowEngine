#pragma once

#include "Platforms/Vulkan/Renderer/VulkanBackend.h"

namespace Snow {
	class Renderer {
	public:
		bool Init(const char* appName, PlatformState* state);
		void Shutdown();

		void OnResize(int width, int height);

		bool DrawFrame(RenderCommand* command);

		static RendererBackend* CreateBackend(RendererType type) {
			switch (type)
			{
				case RENDER_TYPE_VULKAN: { return new VulkanBackend(); break; }
			}
		}
	private: 
		RendererBackend* m_Backend;
	};
}
