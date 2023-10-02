#include "Platform/Platform.h"
#include "Core/Debugger/Logger.h"

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
