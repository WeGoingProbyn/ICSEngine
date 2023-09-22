#pragma once

#include "Core/Application/Application.h"
#include "Core/Application/UserInterface.h"

#include "Core/Geometry/Square.h"

#include "Graphics/RenderFront/Buffers/Indices.h"

extern UserInterface& GetUserInstance();

// Main entry point for application
int main(void)
{
	Square sqr;
	
	Application app;
	app.RunApplication(GetUserInstance());

#ifdef _DEBUG
	app.~Application();
	MemoryStats::CheckMemoryForShutdown();
#endif

	return 0;
}

