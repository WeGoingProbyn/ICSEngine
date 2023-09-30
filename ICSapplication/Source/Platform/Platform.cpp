#include "Defines.h"
#include "Core/Debugger/Logger.h"
#include "Platform/Platform.h"

Platform::Config Platform::m_Config;

Platform::Platform()
	:
	m_Handle()
{
	m_Handle.InternalHandle = nullptr;
}

Platform::~Platform()
{
	m_Handle.InternalHandle = nullptr;
}
