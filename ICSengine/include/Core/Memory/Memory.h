#pragma once

#include "Defines.h"

#include "Core/Memory/MemoryTypes.h"
#include "Core/Memory/MemoryStats.h"
#include "Core/Memory/MemoryPlatform.h"


class Memory
{
public:
	ICS_API Memory();
	ICS_API ~Memory();

	inline Memory(const Memory& mem) = delete;
	inline Memory& operator=(const Memory& mem) = delete;

	template<typename T>
	static bool ZeroMemoryBlock(T* ptr, unsigned int size);
	template<typename T>
	static bool SetMemory(T* dest, int val, unsigned int size);
	template<typename T>
	static T* AllocateMemory(unsigned int size, MemoryType type);
	template<typename T>
	static bool FreeMemory(T* ptr, unsigned int size, MemoryType type);
	template<typename T>
	static bool CopyMemoryBlock(T* dest, const T* src, unsigned int size);
	template<typename T>
	static bool DeepCopyMemoryBlock(T* dest, const T* src, unsigned int size);
public:
	bool m_Initialised;
};

template<typename T>
T* Memory::AllocateMemory(unsigned int size, MemoryType type)
{
	if (size == 0) { ICS_WARN("Memory: Trying to allocate memory of size 0"); return nullptr; }
	if (type == MemoryType::UNKNOWN)
	{
		ICS_WARN("Memory: Allocating unkown memory type is ill-advised");
	}
	MemoryStats::OnMemoryAssign(size, type);
	T* tmp = MemoryPlatform::PlatformMemoryAllocate<T>(size, false);
	//Memory::ZeroMemoryBlock<T>(tmp, size);
	return tmp;
}

template<typename T>
bool Memory::FreeMemory(T* ptr, unsigned int size, MemoryType type)
{
	if (ptr == nullptr || size < 1)
	{
		ICS_ERROR("Memory: Trying to free non existant memory!");
		return false;
	}
	else if (type == MemoryType::UNKNOWN)
	{
		ICS_WARN("Memory: De-allocated unkown memory type");
	}
	MemoryStats::OnMemoryFree(size, type);
	MemoryPlatform::PlatformMemoryFree<T>(ptr);
	ptr = nullptr;
	return true;
}

template<typename T>
bool Memory::ZeroMemoryBlock(T* ptr, unsigned int size)
{
	if (ptr == nullptr || size < 1)
	{
		ICS_ERROR("Memory: Trying to zero non existant memory!");
		return false;
	}
	else
	{
		MemoryPlatform::PlatformMemoryZero<T>(ptr, size);
		return true;
	}
}

template<typename T>
bool Memory::SetMemory(T* dest, int val, unsigned int size)
{
	if (dest == nullptr || size < 1)
	{
		ICS_ERROR("Memory: Trying to set non existant memory!");
		return false;
	}
	else
	{
		MemoryPlatform::PlatformMemorySet<T>(dest, val, size);
		return true;
	}
}

template<typename T>
bool Memory::CopyMemoryBlock(T* dest, const T* src, unsigned int size)
{
	if (dest == nullptr || src == nullptr || size < 1)
	{
		ICS_ERROR("Memory: Trying to copy memory of size %i using nullptr as the %s", size, dest == nullptr ? "dest" : "src");
		return false;
	}
	else
	{
		MemoryPlatform::PlatformMemoryCopy<T>(dest, src, size);
		return true;
	}
}

template<typename T>
bool Memory::DeepCopyMemoryBlock(T* dest, const T* src, unsigned int size)
{
	if (dest == nullptr || src == nullptr || size < 1)
	{
		ICS_ERROR("Memory: Trying to deep copy memory of size %i using nullptr as the %s", size, dest == nullptr ? "dest" : "src");
		return false;
	}
	else
	{
		MemoryPlatform::PlatformMemoryDeepCopy<T>(dest, src, size);
		return true;
	}
}
