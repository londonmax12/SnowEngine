#pragma once
#include "vulkan/vulkan.h"
namespace Snow {
	struct SwapChainSupportInfo {
		VkSurfaceCapabilitiesKHR capibilities;
		uint32_t formatCount;
		VkSurfaceFormatKHR* formats;
		uint32_t presentModeCount;
		VkPresentModeKHR* presentModes;
	};
}