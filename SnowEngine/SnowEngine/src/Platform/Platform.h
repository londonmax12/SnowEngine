#pragma once

namespace Snow {
	struct PlatformState
	{
		void* internalState;
	};

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
}