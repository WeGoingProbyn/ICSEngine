#include "Utilities/FileIO/FileAsString.h"

#include "Core/Memory/Memory.h"
#include "Core/Debugger/Logger.h"

#include <stdio.h>
#include <stdlib.h>

String FileAsString::GetStringFromFile(String file_name)
{
	FILE* file;
	ICS_ASSERT_MSG(fopen_s(&file, file_name.AsCstr(), "r") == 0, "FileAsString: Could not open file using given file name");

	fseek(file, 0, SEEK_END);
	unsigned long size = ftell(file);
	fseek(file, 0, SEEK_SET);

	char* ptr = Memory::AllocateMemory<char>(size, MemoryType::ICS_STRING);
	unsigned int read = (unsigned int)fread(ptr, 1, size, file);
	ptr[read] = '\0';

	fclose(file);
	String out(ptr);
	Memory::FreeMemory(ptr, size, MemoryType::ICS_STRING);
	return out;
}