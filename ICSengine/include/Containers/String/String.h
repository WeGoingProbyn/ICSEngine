#pragma once

#include "Defines.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <iostream>

class String
{
public:
	ICS_API String();
	ICS_API ~String();
	ICS_API String(const char* str);
	ICS_API String(const String& str);
	ICS_API String(const wchar_t* str);
	ICS_API String(String&& str) noexcept;

	ICS_API String& operator=(const char* str);
	ICS_API String& operator=(const String& str);
	ICS_API String& operator=(String&& str) noexcept;

	ICS_API String& operator+ (const String& str);
	ICS_API String& operator+= (const String& str);

	ICS_API bool operator== (const String& str);

	ICS_API wchar_t* AsWideChar();
	ICS_API inline char* AsCstr() { return m_Chars; }
	ICS_API inline unsigned int GetSize() { return m_Size; }
	ICS_API static String& GetVariadicString(const char* str, ...);
private:
	char* m_Chars;
	wchar_t* m_wChars;
	unsigned int m_Size;
	unsigned int m_wSize;
};
