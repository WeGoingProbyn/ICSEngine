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
	
	Indices::Hierachy hierachy;
	hierachy.PushNodeToHierachy(2u, 0u, Indices::Type::TriangleList);
	hierachy.PushNodeToHierachy(5u, 0u, Indices::Type::TriangleList);
	
	Indices indices(hierachy);
	indices.GetBuffer().PushNodeToBuffer(sqr.GetIndices()[0]);
	
	Application app;
	app.RunApplication(GetUserInstance());

#ifdef _DEBUG
	app.~Application();
	MemoryStats::CheckMemoryForShutdown();
#endif

	return 0;
}

