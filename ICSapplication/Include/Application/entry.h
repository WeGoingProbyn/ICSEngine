#pragma once

#include "Application/Application.h"

namespace ICS
{
	extern Application* CreateApplication();
	extern void DestroyApplication(Application* app);
}

// Main entry point for application
int main(void)
{
	Application* app = ICS::CreateApplication();
	app->RunApplication();
	ICS::DestroyApplication(app);

#ifdef _DEBUG
	MemoryStats::CheckMemoryForShutdown();
#endif

	return 0;
}

