#pragma once

#include <vulkan/vulkan.h>

namespace Snow {
	class VulkanDevice {
	public:
		VulkanDevice();
		~VulkanDevice();
	private:
		VkPhysicalDevice m_PhysicalDevice;
		VkDevice m_LogicalDevice;
	};
}