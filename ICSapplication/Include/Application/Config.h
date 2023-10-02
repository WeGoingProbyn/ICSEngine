#pragma once

#include <Defines.h>

class ICS_API Config
{
public:
	struct ICS_API Platform
	{
		unsigned int x;
		unsigned int y;
		unsigned int width;
		unsigned int height;
		const wchar_t* name; // TODO: Change this to be a const char* fuck win32

		Platform() : x(0u), y(0u), width(0u), height(0u), name(L"Default Application") {}

		Platform(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
			:
			x(x), y(y), width(width), height(height), name(L"Default Application") {}
	};

public:
	Config() {}

public:
	static Config::Platform platform;
};