#pragma once

#ifdef SNOW_RENDERER_VULKAN
#include <vulkan/vulkan.h>
#endif
namespace Snow {
	struct PlatformState
	{
		void* internalState;
	};

	// System platform
	void platform_Init();

	bool platform_PumpMessages(PlatformState* state);

	void* platform_Allocate(uint32_t size, bool aligned);
	void platform_Free(void* block, bool aligned);
	void* platform_ZeroMemory(void* block, uint32_t size);
	void* platform_CopyMemory(void* dest, const void* source, uint32_t size);
	void* platform_SetMemory(void* dest, int32_t value, uint32_t size);

	void platform_ConsoleWrite(const char* msg, int color);
	void platform_ConsoleWriteError(const char* msg, int color);

	double platform_GetAbsTime();
	void platform_Sleep(int ms);


	// Renderer Platform
#ifdef SNOW_RENDERER_VULKAN
	void platform_GetExtensionNames(std::vector<const char*>* arr);
	bool platform_CreateVulkanSurface(PlatformState* platState, VkInstance instance, VkAllocationCallbacks* allocator, VkSurfaceKHR* out);
#endif // SNOW_RENDERER_VULKAN
}