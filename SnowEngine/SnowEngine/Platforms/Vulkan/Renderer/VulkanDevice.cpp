#include "snowpch.h"
#include "VulkanDevice.h"

#include "src/Memory/Memory.h"

Snow::VulkanDevice::VulkanDevice(VkInstance instance, VkSurfaceKHR surface)
{
	m_Instance = instance;

	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(instance, &deviceCount, 0);
	if (deviceCount == 0) {
		SNOW_FATAL("Failed to find suported Vulkan device");
	}
	VkPhysicalDevice* a = new VkPhysicalDevice[deviceCount];
	vkEnumeratePhysicalDevices(instance, &deviceCount, a);
	for (int i = 0; i < deviceCount; i++) {

		VkPhysicalDeviceProperties properties;
		vkGetPhysicalDeviceProperties(a[i], &properties);

		VkPhysicalDeviceFeatures features;
		vkGetPhysicalDeviceFeatures(a[i], &features);

		VkPhysicalDeviceMemoryProperties memory;
		vkGetPhysicalDeviceMemoryProperties(a[i], &memory);


		DeviceRequirements info{};
		info.graphics = true;
		info.present = true;
		info.transfer = true;

		info.samplerAnisomtropy = true;
		info.discreteGpu = true; 
		info.extensions.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);

		QueueFamilyInfo queueInfo{};
		bool result = DeviceMeetsRequirements(a[i], surface, &properties, &features, info, &queueInfo, &m_SwapchainInfo);
		if (result) {
			SNOW_INFO("------------------------------------------");
			SNOW_INFO(properties.deviceName);
			SNOW_INFO("");
			switch (properties.deviceType)
			{
			case VK_PHYSICAL_DEVICE_TYPE_OTHER:
				SNOW_INFO("\tGPU type: Unknown", properties.deviceName);
				break;
			case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
				SNOW_INFO("\tGPU type: Integrated", properties.deviceName);
				break;
			case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
				SNOW_INFO("\tGPU type: Discrete", properties.deviceName);
				break;
			case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
				SNOW_INFO("\tGPU type: Virtual", properties.deviceName);
				break;
			case VK_PHYSICAL_DEVICE_TYPE_CPU:
				SNOW_INFO("\tGPU type: CPU", properties.deviceName);
				break;
			default:
				break;
			}
			SNOW_INFO("\tGPU Driver Version: %d.%d.%d", VK_VERSION_MAJOR(properties.driverVersion), VK_VERSION_MINOR(properties.driverVersion), VK_VERSION_PATCH(properties.driverVersion));
			SNOW_INFO("\tVulkan API Version: %d.%d.%d", VK_VERSION_MAJOR(properties.apiVersion), VK_VERSION_MINOR(properties.apiVersion), VK_VERSION_PATCH(properties.apiVersion));
			SNOW_INFO("");
			for (int j = 0; j < memory.memoryHeapCount; j++) {
				float memorySizeGB = ((float)memory.memoryHeaps[j].size) / 1024.f / 1024.f / 1024.f;
				if (memory.memoryHeaps[j].flags & VK_MEMORY_HEAP_DEVICE_LOCAL_BIT) {
					SNOW_INFO("\tLocal GPU memory: %.2f GiB", memorySizeGB);
				}
				else
				{
					SNOW_INFO("\tShared system memory: %.2f GiB", memorySizeGB);
				}
			}
			SNOW_INFO("------------------------------------------");
			m_PhysicalDevice = a[i];

			m_GraphicsIndex = queueInfo.graphicsIndex;
			m_PresentIndex = queueInfo.presentIndex;
			m_TransferIndex = queueInfo.transferIndex;

			m_Properties = properties;
			m_Features = features;
			m_Memory = memory;

			break;
		}
		SNOW_INFO("Selected device: %s", properties.deviceName);
	}

	if (!m_PhysicalDevice) {
		SNOW_ERROR("No physical device which meets requirements was found");
		return;
	}
	delete[] a;
}
Snow::VulkanDevice::~VulkanDevice()
{
}

bool Snow::VulkanDevice::DeviceMeetsRequirements(VkPhysicalDevice device, VkSurfaceKHR surface, const VkPhysicalDeviceProperties* properties, const VkPhysicalDeviceFeatures* features, const DeviceRequirements requirements, QueueFamilyInfo* outQueueFamilyInfo, SwapChainSupportInfo* outSwapchainSupport)
{
	outQueueFamilyInfo->graphicsIndex = -1;
	outQueueFamilyInfo->presentIndex = -1;
	outQueueFamilyInfo->computeIndex = -1;
	outQueueFamilyInfo->transferIndex = -1;

	if (requirements.discreteGpu) {
		if (properties->deviceType != VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
			SNOW_INFO("Device is not a discrete GPU");
			return false;
		}
	}

	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, 0);
	VkQueueFamilyProperties* queueFamilies = new VkQueueFamilyProperties[queueFamilyCount];
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies);

	SNOW_INFO("Graphics | Present | Compute | Transfer | Name");
	int minTransferScore = 255;
	for (int i = 0; i < queueFamilyCount; i++) {
		int transferScore = 0;
		if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
			outQueueFamilyInfo->graphicsIndex = i;
			transferScore++;
		}
		if (queueFamilies[i].queueFlags & VK_QUEUE_COMPUTE_BIT) {
			outQueueFamilyInfo->computeIndex = i;
			transferScore++;
		}
		if (queueFamilies[i].queueFlags & VK_QUEUE_TRANSFER_BIT) {
			if (transferScore <= minTransferScore) {
				minTransferScore = transferScore;
				outQueueFamilyInfo->transferIndex = i;
			}
		}
		VkBool32 supportsPresent = VK_FALSE;
		vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &supportsPresent);
		if (supportsPresent) {
			outQueueFamilyInfo->presentIndex = i;
		}
		SNOW_INFO("       %d |       %d |       %d |        %d | %s", outQueueFamilyInfo->graphicsIndex != -1, outQueueFamilyInfo->presentIndex != -1, outQueueFamilyInfo->computeIndex != -1, outQueueFamilyInfo->transferIndex != -1, properties->deviceName);
		if (
			!requirements.graphics || outQueueFamilyInfo->graphicsIndex != -1 &&
			!requirements.present || outQueueFamilyInfo->presentIndex != -1 &&
			!requirements.compute || outQueueFamilyInfo->computeIndex != -1 &&
			!requirements.transfer || outQueueFamilyInfo->transferIndex != -1)
		{
			SNOW_INFO("Device meets queue requirements");

			QuerySwapchainSupportInfo(device, surface, outSwapchainSupport);

			if (outSwapchainSupport->formatCount < 1 || outSwapchainSupport->presentModeCount < 1) {
				SNOW_INFO("Device does not meet swapchain requirements");
				return false;
			}
			int reqExtensions = requirements.extensions.size();
			if (reqExtensions > 0) {
				uint32_t count;
				vkEnumerateDeviceExtensionProperties(device, nullptr, &count, nullptr);
				std::vector<VkExtensionProperties> extensions(count);
				vkEnumerateDeviceExtensionProperties(device, nullptr, &count, extensions.data());
		
				for (int i = 0; i < reqExtensions; i++) {
					bool found = false;
					for (int j = 0; j < count; j++) {
						if (requirements.extensions[i] == extensions[j].extensionName) {
							found = true;
							break;
						}
					}
					if (!found) {
						SNOW_INFO("Device missing required extension: %s", requirements.extensions[i].c_str());
						return false;
					}
				}
			}
		}
		if (requirements.samplerAnisomtropy && !features->samplerAnisotropy) {
			SNOW_INFO("Device does not support samplerAnisotropy");
			return false;
		}
		return true;
	}
	return false;
	delete [] queueFamilies;
}

void Snow::VulkanDevice::QuerySwapchainSupportInfo(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, SwapChainSupportInfo* outInfo)
{
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, &outInfo->capibilities);
	vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &outInfo->formatCount, outInfo->formats);
	if(outInfo->formatCount != 0) {
		vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &outInfo->formatCount, outInfo->formats);
	}
	vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &outInfo->presentModeCount, 0);
	if (outInfo->presentModeCount != 0) {
		vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &outInfo->presentModeCount, outInfo->presentModes);
	}
}
