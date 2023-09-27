#pragma once

#include "Core/Debugger/Logger.h"

class MemoryPlatform
{
public:
	template<typename T>
	static bool PlatformMemoryFree(T* ptr);
	template<typename T>
	static bool PlatformMemoryZero(T* ptr, unsigned int size);
	template<typename T>
	static T* PlatformMemoryAllocate(unsigned int size, bool aligned);
	template<typename T>
	static bool PlatformMemoryCopy(T* dest, const T* src, unsigned int size);
	template<typename T>
	static bool PlatformMemorySet(T* dest, unsigned int val, unsigned int size);
	template<typename T>
	static bool PlatformMemoryDeepCopy(T* dest, const T* src, unsigned int size);
	template<typename T, typename... Args>
	static T* PlatformAllocateWithCstrctArgs(unsigned int size, bool aligned, Args... args);
};

template<typename T, typename... Args>
T* MemoryPlatform::PlatformAllocateWithCstrctArgs(unsigned int size, bool aligned, Args... args)
{
	if (size > 0)
	{
		return new T[size](args...);
	}
	else
	{
		ICS_ERROR("MemoryPlatform: Could not allocate memory using size 0, allocation is nullptr");
		return nullptr;
	}
}

template<typename T>
bool MemoryPlatform::PlatformMemoryFree(T* ptr)
{
	if (!ptr)
	{
		ICS_ERROR("MemoryPlatform: Trying to free a nullptr");
		return false;
	}
	else
	{
		delete[] ptr;
		return true;
	}
}

template<typename T>
T* MemoryPlatform::PlatformMemoryAllocate(unsigned int size, bool aligned)
{
	if (size > 0)
	{
		return new T[size];
	}
	else
	{
		ICS_ERROR("MemoryPlatform: Could not allocate memory using size 0, allocation is nullptr");
		return nullptr;
	}
}

template<typename T>
bool MemoryPlatform::PlatformMemoryZero(T* ptr, unsigned int size)
{
	if (size > 0)
	{
		std::memset(ptr, 0, size);
		return true;
	}
	else
	{
		ICS_ERROR("MemoryPlatform: Could not zero memory using size 0");
		return false;
	}
}

template<typename T>
bool MemoryPlatform::PlatformMemoryCopy(T* dest, const T* src, unsigned int size)
{
	if (dest == nullptr || src == nullptr || size < 1)
	{
		ICS_ERROR("MemoryPlatform: Could not copy memory, size is 0 or %s is nullptr", dest == nullptr ? "dest" : "src");
		return false;
	}
	else
	{
		std::memcpy(dest, src, size);
		return true;
	}
}

template<typename T>
bool MemoryPlatform::PlatformMemoryDeepCopy(T* dest, const T* src, unsigned int size)
{
	if (dest == nullptr || src == nullptr || size < 1)
	{
		ICS_ERROR("MemoryPlatform: Could not copy memory, size is 0 or %s is nullptr", dest == nullptr ? "dest" : "src");
		return false;
	}
	else
	{
		for (unsigned int index = 0; index < size / sizeof(T); index++)
		{
			dest[index] = src[index];
		}
		return true;
	}
}

template<typename T>
bool MemoryPlatform::PlatformMemorySet(T* dest, unsigned int val, unsigned int size)
{
	if (dest == nullptr || size < 1)
	{
		ICS_ERROR("MemoryPlatform: Could not copy memory, size is 0 or dest is nullptr");
		return false;
	}
	else
	{
		std::memset(dest, val, size);
		return true;
	}
}