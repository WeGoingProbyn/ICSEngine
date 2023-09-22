#pragma once

#include "Defines.h"
#include "Core/Debugger/Logger.h"
#include "Platform/Platform.h"


Platform::Platform()
	:
	m_Handle(),
	m_Config()
{
	m_Handle.InternalHandle = nullptr;
}

Platform::~Platform()
{
	m_Handle.InternalHandle = nullptr;
}
