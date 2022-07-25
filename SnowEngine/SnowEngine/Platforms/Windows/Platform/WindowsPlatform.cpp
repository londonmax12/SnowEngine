#include "snowpch.h"

#ifdef SNOW_PLATFORM_WINDOWS
#include "src/Platform/Platform.h"
#include "../WindowsInternalState.h"

#ifdef SNOW_RENDERER_VULKAN
#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_win32.h>
#endif // SNOW_RENDERER_VULKAN


namespace Snow {
	static double g_ClockFrequency;
	static LARGE_INTEGER g_StartTime;
}

void Snow::platform_Init()
{
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	g_ClockFrequency = 1.0 / (float)freq.QuadPart;
	QueryPerformanceCounter(&g_StartTime);
}

bool Snow::platform_PumpMessages(PlatformState* state)
{
    MSG msg;
	while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}

	return true;
}

void* Snow::platform_Allocate(uint32_t size, bool aligned) {
	return malloc(size);
}
void Snow::platform_Free(void* block, bool aligned) {
	free(block);
}
void* Snow::platform_ZeroMemory(void* block, uint32_t size)
{
	return memset(block, 0, size);
}
void* Snow::platform_CopyMemory(void* dest, const void* source, uint32_t size)
{
	return memcpy(dest, source, size);
}
void* Snow::platform_SetMemory(void* dest, int32_t value, uint32_t size)
{
	return memset(dest, value, size);
}
void Snow::platform_ConsoleWrite(const char* msg, int color) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	static int levels[6] = {12, 4, 6, 7, 1, 8};
	SetConsoleTextAttribute(consoleHandle, levels[color]);
	OutputDebugStringA(msg);
	uint32_t len = strlen(msg);
	LPDWORD numberWritten = 0;
	WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), msg, (DWORD)len, numberWritten, 0);
}
void Snow::platform_ConsoleWriteError(const char* msg, int color)
{
	HANDLE consoleHandle = GetStdHandle(STD_ERROR_HANDLE);
	static int levels[6] = { 12, 4, 6, 7, 1, 8 };
	SetConsoleTextAttribute(consoleHandle, levels[color]);
	OutputDebugStringA(msg);
	uint32_t len = strlen(msg);
	LPDWORD numberWritten = 0;
	WriteConsoleA(GetStdHandle(STD_ERROR_HANDLE), msg, (DWORD)len, numberWritten, 0);
}
double Snow::platform_GetAbsTime()
{
	LARGE_INTEGER timeNow;
	QueryPerformanceCounter(&timeNow);
	return (double)timeNow.QuadPart * g_ClockFrequency;
}
void Snow::platform_Sleep(int ms)
{
	Sleep(ms);
}
#ifdef SNOW_RENDERER_VULKAN
void Snow::platform_GetExtensionNames(std::vector<const char*>* arr)
{
	arr->push_back("VK_KHR_win32_surface");
}
bool Snow::platform_CreateVulkanSurface(PlatformState* platState, VkInstance instance, VkAllocationCallbacks* allocator, VkSurfaceKHR* out)
{
	Snow::InternalState* state = (Snow::InternalState*)platState->internalState;
	VkWin32SurfaceCreateInfoKHR createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	createInfo.hinstance = state->instance;
	createInfo.hwnd = state->hwnd;
	
	VkResult res = vkCreateWin32SurfaceKHR(instance, &createInfo, allocator, out);
	if (res != VK_SUCCESS) {
		SNOW_FATAL("Failed to create Vulkan Win32 surface");
		return false;
	}
	state->surface = *out;
	return true;
}
#endif
#endif