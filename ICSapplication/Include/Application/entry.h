#pragma once

#include "Application/Application.h"
#include "Application/UserInterface.h"

extern UserInterface& GetUserInstance();

// Main entry point for application
int main(void)
{
	Application app;
	app.RunApplication(GetUserInstance());

#ifdef _DEBUG
	app.~Application();
	MemoryStats::CheckMemoryForShutdown();
#endif

	return 0;
}

