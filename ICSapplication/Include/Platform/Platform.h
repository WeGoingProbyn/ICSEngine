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

protected:
	Platform::Config m_Config;
	Platform::PlatformHandle m_Handle;
};
