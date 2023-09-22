#pragma once

#include "Defines.h"

#include "Core/Debugger/Logger.h"

class EventHandler;

class Platform
{
public:
	struct Config
	{
		int x;
		int y;
		int width;
		int height;
		const wchar_t* name;
	};
	struct PlatformHandle 
	{
		void* InternalHandle; 
	};
public:
	Platform();
	virtual ~Platform() = 0;
	virtual bool ReadMessageQueue() = 0;
	inline Platform(const Platform& mem) = delete;
	inline Platform& operator=(const Platform& mem) = delete;

	inline Platform::Config& GetConfig() { return m_Config; }
	inline Platform::PlatformHandle& GetPlatformHandle() { return m_Handle; }

	static void PlatformErrorOut(const char* msg, unsigned int colour);
	static void PlatformConsoleOut(const char* msg, unsigned int colour);

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
protected:
	Platform::Config m_Config;
	Platform::PlatformHandle m_Handle;
};

template<typename T>
bool Platform::PlatformMemoryFree(T* ptr)
{
	if (!ptr)
	{
		ICS_ERROR("Platform: Trying to free a nullptr");
		return false;
	}
	//if constexpr (std::is_same<T, unsigned int>::value)
	//{
	//	delete ptr;
	//	return true;
	//}
	else
	{
		delete[] ptr;
		return true;
	}
}

template<typename T>
T* Platform::PlatformMemoryAllocate(unsigned int size, bool aligned)
{
	if (size > 0)
	{
		return new T[size / sizeof(T)];
	}
	else
	{
		ICS_ERROR("Platform: Could not allocate memory using size 0, allocation is nullptr");
		return nullptr;
	}
}

template<typename T>
bool Platform::PlatformMemoryZero(T* ptr, unsigned int size)
{
	if (size > 0)
	{
		std::memset(ptr, 0, size);
		return true;
	}
	else
	{
		ICS_ERROR("Platform: Could not zero memory using size 0");
		return false;
	}
}

template<typename T>
bool Platform::PlatformMemoryCopy(T* dest, const T* src, unsigned int size)
{
	if (dest == nullptr || src == nullptr || size < 1)
	{
		ICS_ERROR("Platform: Could not copy memory, size is 0 or %s is nullptr", dest == nullptr ? "dest" : "src");
		return false;
	}
	else
	{
		std::memcpy(dest, src, size);
		return true;
	}
}

template<typename T>
bool Platform::PlatformMemoryDeepCopy(T* dest, const T* src, unsigned int size)
{
	if (dest == nullptr || src == nullptr || size < 1)
	{
		ICS_ERROR("Platform: Could not copy memory, size is 0 or %s is nullptr", dest == nullptr ? "dest" : "src");
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
bool Platform::PlatformMemorySet(T* dest, unsigned int val, unsigned int size)
{
	if (dest == nullptr || size < 1)
	{
		ICS_ERROR("Platform: Could not copy memory, size is 0 or dest is nullptr");
		return false;
	}
	else
	{
		std::memset(dest, val, size);
		return true;
	}
}