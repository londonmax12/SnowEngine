#include "snowpch.h"
#include "VulkanBackend.h"

bool Snow::VulkanBackend::Init(const char* applicationName, PlatformState* m_PlatformState)
{
	m_Allocator = 0;

	VkApplicationInfo appInfo{};
	appInfo.apiVersion = VK_API_VERSION_1_3;
	appInfo.pApplicationName = applicationName;
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "Snow Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);

	VkInstanceCreateInfo createInfo{};
	createInfo.pApplicationInfo = &appInfo;

	VkResult res = vkCreateInstance(&createInfo, m_Allocator, &m_Instance);
	if (res != VK_SUCCESS) {
		SNOW_ERROR("Failed to create Vulkan instance: %u", res);
		return false;;
	}

	SNOW_INFO("Initialized Vulkan renderer");
	return true;
}

void Snow::VulkanBackend::Shutdown()
{
} 

void Snow::VulkanBackend::Resized(int width, int height)
{
}

bool Snow::VulkanBackend::BeginFrame(DeltaTime dt)
{
	return true;
}

bool Snow::VulkanBackend::EndFrame(DeltaTime dt)
{
	return true;
}
