#pragma once

#include "Defines.h"

#include "Core/Memory/MemoryTypes.h"

class MemoryStats
{
private:

public:
	ICS_API static char* GetMemoryAllocations();
	ICS_API static bool CheckMemoryForShutdown();

	ICS_API static void OnMemoryFree(unsigned int size, MemoryType type);
	ICS_API static void OnMemoryAssign(unsigned int size, MemoryType type);
public:
	static unsigned int allocated;
	static unsigned int totalallocated;
	static const char* Strings[static_cast<unsigned int>(MemoryType::MAX_TERMS)];
	static unsigned int allocatedtags[static_cast<unsigned int>(MemoryType::MAX_TERMS)];
};