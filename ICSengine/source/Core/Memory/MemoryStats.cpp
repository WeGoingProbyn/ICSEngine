#include "Core/Memory/MemoryStats.h"

// TODO: Remove no?
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdarg.h>

#include "Core/Debugger/Logger.h"

// These seem better off as static parts so that the
// memory manipulation functions can be called statically
// throughout the engine...

unsigned int MemoryStats::allocated = 0u;
unsigned int MemoryStats::totalallocated = 0u;
unsigned int MemoryStats::allocatedtags[static_cast<unsigned int>(MemoryType::MAX_TERMS)] = { 0u };

const char* MemoryStats::Strings[static_cast<unsigned int>(MemoryType::MAX_TERMS)] = {
		"UNKNOWN		",
		"ICS_SCENE		",
		"ICS_MODEL		",
		"ICS_SHADER		",
		"ICS_TEXTURE		",
		"ICS_RENDERER		",
		"ICS_STACK_MANAGER	",
		"ICS_ARRAY		",
		"ICS_DARRAY		",
		"ICS_STRING		",
		"ICS_APPLICATION	",
		"USER_OWNED		",
};

bool MemoryStats::CheckMemoryForShutdown()
{
	//unsigned int ignore_memory_obj = 1u;
	if (MemoryStats::totalallocated > 0u)
	{
		ICS_ERROR("Memory: There are still live pointers on shutdown! Total: %i", MemoryStats::totalallocated);
		ICS_DEBUG(MemoryStats::GetMemoryAllocations());
		return false;
	}
	else
	{
		ICS_DEBUG(MemoryStats::GetMemoryAllocations());
		return true;
	}
}

char* MemoryStats::GetMemoryAllocations()
{
	// allocated tags is in raw number of bytes allocated.
	// Need to convert to something more useful like Mb etc.
	unsigned int kBit = 1024;
	unsigned int mBit = 1024 * kBit;
	unsigned int gBit = 1024 * mBit;

	const unsigned int buffmax = 10000;
	char buff[buffmax] = "Tagged Memory Allocations:\n";
	unsigned int length = (unsigned int)strlen(buff);
	for (unsigned int i = 0; i < static_cast<unsigned int>(MemoryType::MAX_TERMS); i++)
	{
		char units[3] = "XB";
		float size = 1.0f;
		if (MemoryStats::allocatedtags[i] >= gBit) { units[0] = 'g'; size = MemoryStats::allocatedtags[i] / (float)gBit; }
		else if (MemoryStats::allocatedtags[i] >= mBit) { units[0] = 'm'; size = MemoryStats::allocatedtags[i] / (float)mBit; }
		else if (MemoryStats::allocatedtags[i] >= kBit) { units[0] = 'k'; size = MemoryStats::allocatedtags[i] / (float)kBit; }
		else { units[0] = 'B'; units[1] = 0; size = (float)MemoryStats::allocatedtags[i]; }
		length += snprintf(buff + length, buffmax, " %s: %.2f%s\n", MemoryStats::Strings[i], size, units);
	}
	return _strdup(buff);
}

void MemoryStats::OnMemoryAssign(unsigned int size, MemoryType type)
{
	MemoryStats::totalallocated++;
	MemoryStats::allocated += size;
	MemoryStats::allocatedtags[static_cast<unsigned int>(type)] += size;
}

void MemoryStats::OnMemoryFree(unsigned int size, MemoryType type)
{
	MemoryStats::totalallocated--;
	MemoryStats::allocated -= size;
	MemoryStats::allocatedtags[static_cast<unsigned int>(type)] -= size;
}