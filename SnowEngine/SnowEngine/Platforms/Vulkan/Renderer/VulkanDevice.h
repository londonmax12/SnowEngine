#pragma once

#include <vulkan/vulkan.h>

#include "InfoStructs.h"

namespace Snow {
	struct DeviceRequirements {
		bool graphics;
		bool present;
		bool compute;
		bool transfer;

		std::vector<std::string> extensions;
		bool samplerAnisomtropy;
		bool discreteGpu;
	};

	struct QueueFamilyInfo {
		int graphicsIndex;
		int presentIndex;
		int computeIndex;
		int transferIndex;
	};

	class VulkanDevice {
	public:
		VulkanDevice(VkInstance instance, VkSurfaceKHR surface, VkAllocationCallbacks* allocator);
		~VulkanDevice();
	private:
		bool DeviceMeetsRequirements(VkPhysicalDevice device,
			VkSurfaceKHR surface,
			const VkPhysicalDeviceProperties* properties,
			const VkPhysicalDeviceFeatures* features,
			const DeviceRequirements requirements,
			QueueFamilyInfo* outQueueFamilyInfo,
			SwapChainSupportInfo* outSwapchainSupport);
		void QuerySwapchainSupportInfo(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, SwapChainSupportInfo* outInfo);
		VkPhysicalDevice m_PhysicalDevice;
		VkDevice m_LogicalDevice;
		VkInstance m_Instance;
		SwapChainSupportInfo m_SwapchainInfo;

		int m_GraphicsIndex;
		int m_PresentIndex;
		int m_TransferIndex;

		VkPhysicalDeviceProperties m_Properties;
		VkPhysicalDeviceFeatures m_Features;
		VkPhysicalDeviceMemoryProperties m_Memory;
		VkAllocationCallbacks* m_Allocator;
	};
}