#pragma once

#include "defines.h"
#include "Core/Debugger/Assertion.h"
#include "Containers/String/String.h"

#define LOG_WARN 1
#define LOG_INFO 1
#define LOG_DEBUG 1
#define LOG_TRACE 1

#if ICS_RELEASE == 1
#define LOG_DEBUG 0
#define LOG_TRACE 0
#endif

class Logger
{
public:
	enum struct LogLevel : unsigned int
	{
		FATAL = 0u,
		_ERROR = 1u,
		WARN = 2u,
		INFO = 3u,
		DEBUG = 4u,
		TRACE = 5u
	};
public:
	ICS_API Logger();
	ICS_API ~Logger();

	ICS_API static void LogToOutput(Logger::LogLevel level, String& string);
	ICS_API static void LogHRESULTOutput(Logger::LogLevel level, HRESULT result);
};

#ifdef ICS_PLATFORM_WINDOWS
#define ICS_HRESULT_CHECK(result) if (FAILED(result)) { Logger::LogHRESULTOutput(Logger::LogLevel::FATAL, result); }
#endif

#ifndef ICS_FATAL
#define ICS_FATAL(message, ...) Logger::LogToOutput(Logger::LogLevel::FATAL, String::GetVariadicString(message, ##__VA_ARGS__));
#endif

#ifndef ICS_ERROR
#define ICS_ERROR(message, ...) Logger::LogToOutput(Logger::LogLevel::_ERROR, String::GetVariadicString(message, ##__VA_ARGS__));
#endif

#if LOG_WARN == 1
#ifndef ICS_WARN
#define ICS_WARN(message, ...) Logger::LogToOutput(Logger::LogLevel::WARN, String::GetVariadicString(message, ##__VA_ARGS__));
#endif
#else
#define ICS_WARN(message, ...)
#endif

#if LOG_INFO == 1
#ifndef ICS_INFO
#define ICS_INFO(message, ...) Logger::LogToOutput(Logger::LogLevel::INFO, String::GetVariadicString(message, ##__VA_ARGS__));
#endif
#else
#define ICS_INFO(message, ...)
#endif

#if LOG_DEBUG == 1
#ifndef ICS_DEBUG
#define ICS_DEBUG(message, ...) Logger::LogToOutput(Logger::LogLevel::DEBUG, String::GetVariadicString(message, ##__VA_ARGS__));
#endif
#else
#define ICS_DEBUG(message, ...)
#endif

#if LOG_TRACE == 1
#ifndef ICS_TRACE
#define ICS_TRACE(message, ...) Logger::LogToOutput(Logger::LogLevel::TRACE, String::GetVariadicString(message, ##__VA_ARGS__));
#endif
#else
#define ICS_TRACE(message, ...)
#endif


#define CHECK_DX11_MSG_QUEUE(call, infoqueue) infoqueue.SetCorrectIndexForMessages(); (call); { auto msg = infoqueue.GetInfoMessages(); if(msg.Size()) { ICS_FATAL(msg[0].AsCstr()); } }
