#include "Containers/String/String.h"
#include "Core/Debugger/Logger.h"
#include "Core/Memory/Memory.h"

String::String()
	:
	m_Size(1),
	m_wSize(1),
	m_wChars(nullptr)
{
	m_Chars = Memory::AllocateMemory<char>(m_Size, MemoryType::ICS_STRING);
	if (m_Chars == nullptr) { ICS_ERROR("String: String allocation returned nullptr"); }
}

String::~String()
{
	if (m_Chars)
	{
		Memory::FreeMemory(m_Chars, sizeof(char) * m_Size, MemoryType::ICS_STRING);
		m_Chars = nullptr;
	}
	if (m_wChars)
	{
		Memory::FreeMemory(m_Chars, sizeof(wchar_t) * m_Size, MemoryType::ICS_STRING);
		m_wChars = nullptr;
	}
	m_Size = 0u;
}

String::String(const char* str)
{
	m_wSize = 0u;
	m_wChars = nullptr;
	// Need to include null terminator
	m_Size = (unsigned int)strlen(str) + 1;
	m_Chars = Memory::AllocateMemory<char>(m_Size, MemoryType::ICS_STRING);
	if (m_Chars == nullptr) { ICS_ERROR("String: String allocation returned nullptr"); }
	else { Memory::CopyMemoryBlock(m_Chars, str, sizeof(char) * m_Size); }
}

String::String(const wchar_t* str)
{
	m_wSize = 0u;
	m_wChars = nullptr;

	m_wSize = (unsigned int)wcslen(str) + 1;
	m_Chars = Memory::AllocateMemory<char>(m_Size, MemoryType::ICS_STRING);
	wcstombs_s(nullptr, m_Chars, m_Size, str, m_Size);
	m_Chars[m_Size] = '\0';
}

String::String(const String& str)
{
	m_Size = str.m_Size;
	m_Chars = Memory::AllocateMemory<char>(m_Size, MemoryType::ICS_STRING);
	if (m_Chars == nullptr) { ICS_ERROR("String: String allocation returned nullptr"); }
	else { Memory::CopyMemoryBlock(m_Chars, str.m_Chars, sizeof(char) * m_Size); }
}

String::String(String&& str) noexcept
{
	*this = String(str);
	if (m_Chars)
	{
		Memory::FreeMemory(str.m_Chars, str.m_Size, MemoryType::ICS_STRING);
		m_Chars = nullptr;
	}
	if (m_wChars)
	{
		Memory::FreeMemory(m_Chars, sizeof(wchar_t) * m_Size, MemoryType::ICS_STRING);
		m_wChars = nullptr;
	}
}

String& String::operator=(const char* str)
{
	if (m_Chars)
	{
		Memory::FreeMemory(m_Chars, m_Size, MemoryType::ICS_STRING);
	}
	m_Size = (unsigned int)strlen(str) + 1;
	m_Chars = Memory::AllocateMemory<char>(m_Size, MemoryType::ICS_STRING);
	if (m_Chars == nullptr) { ICS_ERROR("String: Could not allocate memory on = operation"); return *this; }
	else { Memory::CopyMemoryBlock(m_Chars, str, m_Size); return *this; };
}

String& String::operator=(const String& str)
{
	if (m_Chars)
	{
		Memory::FreeMemory(m_Chars, m_Size, MemoryType::ICS_STRING);
	}
	m_Size = str.m_Size;
	m_Chars = Memory::AllocateMemory<char>(m_Size, MemoryType::ICS_STRING);
	if (m_Chars == nullptr) { ICS_ERROR("String: Could not allocate memory on = operation"); return *this; }
	else { Memory::CopyMemoryBlock(m_Chars, str.m_Chars, m_Size); return *this; };
}

String& String::operator=(String&& str) noexcept
{
	return *this;
}

bool String::operator==(const String& str)
{
	for (unsigned int index = 0; index < m_Size; index++)
	{
		if (m_Chars[index] != str.m_Chars[index])
		{
			return false;
		}
	}
	return true;
}

String& String::operator+ (const String& str)
{
	// Need a temporary buffer to hold the concatenated strings
	// Also ensure the memory for the original string is freed once coped
	char* ptr;
	unsigned int ptrsize = m_Size + str.m_Size;
	ptr = Memory::AllocateMemory<char>(ptrsize, MemoryType::ICS_STRING);
	snprintf(ptr, ptrsize, "%s%s", m_Chars, str.m_Chars);
	Memory::FreeMemory(m_Chars, m_Size, MemoryType::ICS_STRING);

	// Find the new string size and allocated enough memory to hold it
	// copy memory from temporary pointer and clean up unused memory.
	m_Size = (unsigned int)strlen(ptr) + 1;
	m_Chars = Memory::AllocateMemory<char>(m_Size, MemoryType::ICS_STRING);
	Memory::CopyMemoryBlock(m_Chars, ptr, m_Size);
	Memory::FreeMemory(ptr, ptrsize, MemoryType::ICS_STRING);
	return *this;
}


String& String::operator+= (const String& str)
{
	unsigned int ptrsize = m_Size + str.m_Size - 1;
	char* ptr = Memory::AllocateMemory<char>(ptrsize, MemoryType::ICS_STRING);
	if (ptr == nullptr) { return *this; }
	else { snprintf(ptr, ptrsize, "%s%s", m_Chars, str.m_Chars); }

	if (Memory::FreeMemory(m_Chars, m_Size, MemoryType::ICS_STRING))
	{
		// Find the new string size and tell m_chars to point to the new ptr
		m_Size = (unsigned int)strlen(ptr) + 1;
		m_Chars = ptr;
	}
	else
	{
		ICS_ERROR("String: Could not free original memory on + operation")
	}

	return *this;
}

wchar_t* String::AsWideChar()
{
	if (m_wChars)
	{
		Memory::FreeMemory(m_wChars, m_wSize, MemoryType::ICS_STRING);
	}

	m_wChars = Memory::AllocateMemory<wchar_t>(m_wSize, MemoryType::ICS_STRING); // +1 for null-terminator
	mbstowcs_s(nullptr, m_wChars, m_Size - 1, m_Chars, m_Size);
	m_wChars[m_Size] = L'\0';
	return m_wChars;
}

String& String::GetVariadicString(const char* str, ...)
{
	va_list args;
	va_start(args, str);

	// NOTE: I'm pretty sure that _vcsprint is a MSVC only function....
	unsigned int buffer = _vscprintf(str, args) + 1;
	// TODO: check these
	// NOTE: The memory allocated for out needs to be handeled when called
	char* ptr = Memory::AllocateMemory<char>(buffer, MemoryType::ICS_STRING);
	String* out = Memory::AllocateMemory<String>(sizeof(String), MemoryType::ICS_APPLICATION);
	if (ptr == nullptr || out == nullptr)
	{
		ICS_ERROR("String: Could not allocate memory for variadic string construction, returned string is likely bad memory");
		return *out;
	}
	vsnprintf(ptr, buffer, str, args);
	va_end(args);
	*out = ptr;
	Memory::FreeMemory(ptr, buffer, MemoryType::ICS_STRING);
	return *out;
}
