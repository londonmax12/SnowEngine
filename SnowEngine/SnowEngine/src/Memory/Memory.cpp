#include "snowpch.h"
#include "Memory.h"
#include "../Platform/Platform.h"

const char* Snow::Memory::MemoryTypeToString(MemoryType type)
{
	switch (type) {
		case MemoryType::MEMORY_TYPE_OTHER:
		{
			return "Other:   ";
		}
		default:
		{
			return "Unknown: ";
		}
	}
}

void Snow::Memory::MemInit()
{
	platform_ZeroMemory(&m_Stats, sizeof(m_Stats));
}

void Snow::Memory::MemShutdown()
{
}

void* Snow::Memory::MemAllocate(uint64_t size, MemoryType type)
{
	m_Stats.total += size;
	m_Stats.typeAllocations[type] += size;

	void* block = platform_Allocate(size, false);
	platform_ZeroMemory(block, size);
	return block;
}

void Snow::Memory::MemFree(void* block, uint64_t size, MemoryType type)
{
	m_Stats.total -= size;
	m_Stats.typeAllocations[type] -= size;

	platform_Free(block, false);
}

void* Snow::Memory::MemZeroMemory(void* block, uint64_t size)
{
	return platform_ZeroMemory(block, size);
}

void* Snow::Memory::MemCopyMemory(void* dest, const void* source, uint64_t size)
{
	return platform_CopyMemory(dest, source, size);
}

void* Snow::Memory::MemSetMemory(void* dest, int32_t value, uint64_t size)
{
	return platform_SetMemory(dest, value, size);
}

char* Snow::Memory::PrintPerformance()
{
	const uint64_t kb = 1024;
	const uint64_t mb = 1048576;
	const uint64_t gb = 1073741824;

	SNOW_INFO("====== System Memory Usage ======");
	for (int i = 0; i < MEMORYMAXTYPES; i++) {
		const char* unit = "B";
		float amount = 0.0f;
		if (m_Stats.typeAllocations[i] >= kb) {
			unit = "KB";
			amount = m_Stats.typeAllocations[i] / kb;
		}
		if (m_Stats.typeAllocations[i] >= mb) {
			unit = "MB";
			amount = m_Stats.typeAllocations[i] / mb;
		}
		else if (m_Stats.typeAllocations[i] >= gb) {
			unit = "GB";
			amount = m_Stats.typeAllocations[i] / gb;
		}
		else {
			amount = m_Stats.typeAllocations[i];
		}
		const char* label = MemoryTypeToString((MemoryType)i);
		SNOW_INFO("%s%f", label, amount);
		
	}
	SNOW_INFO("=================================");
	return nullptr;
}
