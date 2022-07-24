#pragma once
#include "src/Renderer/RendererBackend.h"
#include "vulkan/vulkan.h"

namespace Snow {
	class VulkanBackend : public RendererBackend {
	public:
		bool Init(const char* applicationName, PlatformState* m_PlatformState);
		void Shutdown();
		void Resized(int width, int height);

		bool BeginFrame(DeltaTime dt);
		bool EndFrame(DeltaTime dt);
	private:
		VkInstance m_Instance;
		VkAllocationCallbacks* m_Allocator;
#ifdef _DEBUG
		VkDebugUtilsMessengerEXT m_Messenger;
#endif // _DEBUG

	};
}