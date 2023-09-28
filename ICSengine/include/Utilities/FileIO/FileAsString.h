#pragma once

#include "Containers/String/String.h"

class FileAsString
{
public:
	ICS_API static String GetStringFromFile(String file_name);
};