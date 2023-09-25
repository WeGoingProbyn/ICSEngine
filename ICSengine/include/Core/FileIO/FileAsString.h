#pragma once

#include "Containers/String/String.h"

class FileAsString
{
public:
	ICS_API static void GetStringFromFile(String file_name, String& out);
};