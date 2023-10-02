#include <Application/entry.h>

#include "Game.h"
#include "WorldSpace.h"

#include <Managers/Assets.h>
#include <Application/Config.h>

Application* ICS::CreateApplication()
{ 
	Config::platform.x = 0u;
	Config::platform.y = 0u;
	Config::platform.width = 1200u;
	Config::platform.height = 720u;
	Config::platform.name = L"ICS engine";

	Game* app = Memory::AllocateMemory<Game>(1u, MemoryType::ICS_APPLICATION);

	// Any user defined logic should go here, things like event listeners and the like
	app->RegisterEvent(EventListener::EventTypes::ICS_APPLICATION_QUIT, ICS_KeyCodes::KEY_ESCAPE, ICS_KeyCodes::KEY_F9);
	app->RegisterEvent(EventListener::EventTypes::ICS_MEMORY_QUERY_ALLOC, ICS_KeyCodes::KEY_F1);

	// User needs to define the derived layer object, These layers
	// must also be manually deleted by the user in destroy application
	// the arguments are passed as types through the template
	app->GetLayers().PushLayer<WorldSpace>();
	return app;
}

void ICS::DestroyApplication(Application* app)
{
	app->GetLayers().DestroyLayers<WorldSpace>();
	Memory::FreeMemory(app, 1u, MemoryType::ICS_APPLICATION);
}