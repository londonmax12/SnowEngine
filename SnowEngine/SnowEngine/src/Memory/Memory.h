#pragma once
#include <cstdint>

namespace Snow {
	enum MemoryType
	{
		MEMORY_TYPE_OTHER,
		MEMORY_TYPE_RENDERER,

		MEMORYMAXTYPES,
	};
	


	class Memory {
	private:
		struct MemoryStats {
			uint64_t total;
			uint64_t typeAllocations[MEMORYMAXTYPES];
		};

		static inline MemoryStats m_Stats = MemoryStats();

		static const char* MemoryTypeToString(MemoryType type);
	public:
		static void MemInit();
		static void MemShutdown();

		static void* MemAllocate(uint64_t size, MemoryType type);
		static void MemFree(void* block, uint64_t size, MemoryType type);
		static void* MemZeroMemory(void* block, uint64_t size);
		static void* MemCopyMemory(void* dest, const void* source, uint64_t size);
		static void* MemSetMemory(void* dest, int32_t value, uint64_t size);

		static char* PrintPerformance();
	};
}