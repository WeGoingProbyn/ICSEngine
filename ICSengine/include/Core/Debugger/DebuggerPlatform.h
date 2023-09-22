#pragma once

#include "Defines.h"

class DebuggerPlatform
{
public:
	ICS_API static void PlatformErrorOut(const char* msg, unsigned int colour);
	ICS_API static void PlatformConsoleOut(const char* msg, unsigned int colour);
};