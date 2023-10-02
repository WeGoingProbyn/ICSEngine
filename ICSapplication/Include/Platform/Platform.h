#pragma once

#include "Defines.h"

#include "Core/Debugger/Logger.h"

class EventHandler;

class ICS_API Platform
{
public:
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
	inline Platform::PlatformHandle& GetPlatformHandle() { return m_Handle; }

protected:
	Platform::PlatformHandle m_Handle;
};
