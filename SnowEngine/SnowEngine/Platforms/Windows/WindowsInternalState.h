#pragma once
#include <Windows.h>

#ifdef SNOW_RENDERER_VULKAN
#include <vulkan/vulkan.h>
#endif

namespace Snow {
	struct InternalState {
		HINSTANCE instance;
		HWND hwnd;
#ifdef SNOW_RENDERER_VULKAN
		VkSurfaceKHR surface;
#endif
	};
}