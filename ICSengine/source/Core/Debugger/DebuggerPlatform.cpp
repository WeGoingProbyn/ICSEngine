#include "Core/Debugger/DebuggerPlatform.h"

#ifdef ICS_PLATFORM_WINDOWS

void DebuggerPlatform::PlatformErrorOut(const char* msg, unsigned int colour)
{
	// Windows specific console handle
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	// Logger::LogLevel mirror
	static unsigned int level[6] = { 64, 4, 6, 2, 1, 8 };
	SetConsoleTextAttribute(console, level[colour]);
	OutputDebugStringA(msg);
	unsigned int length = (unsigned int)strlen(msg);
	LPDWORD written = 0;
	WriteConsoleA(console, msg, (DWORD)length, written, 0);
	SetConsoleTextAttribute(console, (0 | 7)); // (0 | 7) is black background, white text
}

void DebuggerPlatform::PlatformConsoleOut(const char* msg, unsigned int colour)
{
	// Windows specific console handle
	HANDLE console = GetStdHandle(STD_ERROR_HANDLE);
	// Logger::LogLevel mirror
	static unsigned int level[6] = { (BACKGROUND_RED), (BACKGROUND_RED | BACKGROUND_INTENSITY), (BACKGROUND_RED | BACKGROUND_BLUE), 13, 15, 8 };
	SetConsoleTextAttribute(console, level[colour]);
	OutputDebugStringA(msg);
	unsigned int length = (unsigned int)strlen(msg);
	LPDWORD written = 0;
	WriteConsoleA(console, msg, (DWORD)length, written, 0);
	SetConsoleTextAttribute(console, (0 | 7)); // (0 | 7) is black background, white text
}

#endif