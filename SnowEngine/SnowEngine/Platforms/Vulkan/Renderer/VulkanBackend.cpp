#include "snowpch.h"
#include "VulkanBackend.h"

#include "src/Platform/Platform.h" 

#include <vector>


VKAPI_ATTR VkBool32 VKAPI_CALL vkDebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageTypes, const VkDebugUtilsMessengerCallbackDataEXT* callbackData, void* userData)
{
	switch (messageSeverity)
	{
	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
		SNOW_TRACE(callbackData->pMessage);
		break;
	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
		SNOW_INFO(callbackData->pMessage);
		break;
	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
		SNOW_WARN(callbackData->pMessage);
		break;
	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
		SNOW_ERROR(callbackData->pMessage);
		break;
	default:
		break;
	}
	return VK_FALSE;
}
Snow::VulkanBackend::VulkanBackend()
{
}
Snow::VulkanBackend::~VulkanBackend()
{
	delete m_Device;
}
bool Snow::VulkanBackend::Init(const char* applicationName, PlatformState* platformState)
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

	std::vector<const char*> extensions;
	extensions.push_back(VK_KHR_SURFACE_EXTENSION_NAME);
	platform_GetExtensionNames(&extensions);
#ifdef _DEBUG
	extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

	SNOW_DEBUG("Required Extensions: ");
	for (int i = 0; i < extensions.size(); i++) {
		SNOW_DEBUG("\t| %s", extensions[i]);
	}
#endif // _DEBUG


	createInfo.enabledExtensionCount = extensions.size();
	const char* const* extenstionArray = extensions.data();
	createInfo.ppEnabledExtensionNames = extenstionArray;

	std::vector<const char*> validationLayers;

#ifdef _DEBUG
	SNOW_INFO("Validation layers enabled");

	validationLayers.push_back("VK_LAYER_KHRONOS_validation");

	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
	std::vector<VkLayerProperties> availableLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

	for (int i = 0; i < validationLayers.size(); i++) {
		bool found = 0;
		for (int j = 0; j < layerCount; j++) {
			if (strcmp(validationLayers[i], availableLayers[j].layerName) == 0) {
				found = true;
				SNOW_INFO("Found layer: %s", validationLayers[i]);
				break;
			}
		}
		if (!found) {
			SNOW_FATAL("Required validation layer not found: %s", validationLayers[i]);
			return false;
		}
	}
	SNOW_INFO("All required validation layers found");
#endif // _DEBUG


	createInfo.enabledLayerCount = validationLayers.size();
	const char* const* validationLayersArr = validationLayers.data();
	createInfo.ppEnabledLayerNames = validationLayersArr;

	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;

	VkResult res = vkCreateInstance(&createInfo, m_Allocator, &m_Instance);
	if (res != VK_SUCCESS) {
		SNOW_ERROR("Failed to create Vulkan instance: %u", res);
		return false;;
	}

#ifdef _DEBUG
	SNOW_DEBUG("Creating Vulkan Debugger");
	unsigned int log_severity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT;

	VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo = { VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT };
	debugCreateInfo.messageSeverity = log_severity;
	debugCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT;
	debugCreateInfo.pfnUserCallback = vkDebugCallback;

	PFN_vkCreateDebugUtilsMessengerEXT func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(m_Instance, "vkCreateDebugUtilsMessengerEXT");
	VkResult result = func(m_Instance, &debugCreateInfo, m_Allocator, &m_Messenger);
#endif

	SNOW_DEBUG("Creating Vulkan surface");
	if (!platform_CreateVulkanSurface(platformState, m_Instance, m_Allocator, &m_Surface))
	{
		SNOW_ERROR("Failed to create platform surface");
		return false;
	}

	SNOW_INFO("Created Vulkan instance");


	m_Device = new VulkanDevice(m_Instance, m_Surface);
	return true;
}

void Snow::VulkanBackend::Shutdown()
{
	if (m_Messenger) {
		PFN_vkDestroyDebugUtilsMessengerEXT func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(m_Instance, "vkDestroyDebugUtilsMessengerEXT");
		func(m_Instance, m_Messenger, m_Allocator);
	}
	SNOW_DEBUG("Destroying Vulkan instance");
	vkDestroyInstance(m_Instance, m_Allocator);
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