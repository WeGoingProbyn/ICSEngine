#include "Platform/Platform.h"
#include "Core/Debugger/Logger.h"
#include "Core/Debugger/Assertion.h"
#include "Core/Memory/Memory.h"

ICS_API Logger::Logger()
{
	// TODO: create a system to handle file logs
}

ICS_API Logger::~Logger()
{
	// TODO: Cleanup file IO
}

ICS_API void Logger::LogToOutput(Logger::LogLevel level, String& string)
{
	bool important = static_cast<unsigned int>(level) < static_cast<unsigned int>(Logger::LogLevel::_ERROR);
	const char* strings[6] = { "[FATAL]: ", "[ERROR]: ", "[WARN]: ", "[INFO]: ", "[DEBUG]: ", "[TRACE]: " };
	String str = strings[static_cast<unsigned int>(level)];
	str += string;
	str += "\n";
	// NOTE: Because  the references string passed by the function is allocated dynamically, the destructor must be called explicitly,
	// NOTE: This caused me a massive fucking headache... and im not even sure if it is entirely fixed... Need to add 2 to the size because....
	string.~String();
	Memory::FreeMemory(&string, sizeof(String), MemoryType::ICS_APPLICATION);
	if (important) { Platform::PlatformErrorOut(str.AsCstr(), static_cast<unsigned int>(level)); }
	else { Platform::PlatformConsoleOut(str.AsCstr(), static_cast<unsigned int>(level)); }
}

void Logger::LogHRESULTOutput(Logger::LogLevel level, HRESULT result) {
	wchar_t* Win32MessageBuffer = nullptr;
	const DWORD MessageLength = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, result,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPWSTR)&Win32MessageBuffer, 0, nullptr);

	String string(Win32MessageBuffer);
	LocalFree(Win32MessageBuffer);
	Logger::LogToOutput(level, string);
}

ICS_API void Assertion::AssertionFailed(const char* expr, const char* msg, const char* file, unsigned int line)
{
	Logger::LogToOutput(Logger::LogLevel::FATAL, String::GetVariadicString("Assertion Failed: %s, Message: %s\n         File: %s, Line: %d\n", expr, msg, file, line));
}