#include "Managers/Assets.h"
#include "Application/Config.h"
#include "Application/Application.h"

#include <Core/Debugger/Logger.h>
#include <Utilities/FileIO/FileAsString.h>

#include <Core/Structures/Geometry/Square.h>
#include <Core/Structures/Geometry/Cube.h>

Application::Application() 
{
	m_ShouldRun = true;
	m_ShouldPause = false;
	
	// Register the application instance as an active event listener
	RegisterListener(reinterpret_cast<EventListener&>(*this));

	Assets::OnStartUp();
	m_Render = { Config::platform.width, Config::platform.height, m_Platform.GetPlatformHandle().InternalHandle };
	ICS_INFO("Application created");
}

Application::~Application() 
{
	m_ShouldRun = false;
	m_ShouldPause = false;
	Assets::OnShutDown();
	ICS_INFO("Application destroyed");
}

void Application::LoadSimpleAssets()
{
	// Add some basic geometry to the mesh stack
	Assets::PushToStack<Mesh>("Cube", Cube());
	Assets::PushToStack<Mesh>("Square", Square());

	Constants::Layout const_layout(Constants::Types::MATRIX);
	Shaders::Layout simple_layout(Shaders::Platform::DIRECTX, Shaders::Types::VERTEX, Shaders::Types::PIXEL);
	Assets::PushToStack<Shaders>("Simple", simple_layout, const_layout);
	Assets::Get<Shaders>("Simple").PushSource(FileAsString::GetStringFromFile("Resource/Shader/VertexShader.hlsl"));
	Assets::Get<Shaders>("Simple").PushSource(FileAsString::GetStringFromFile("Resource/Shader/PixelShader.hlsl"));
}

bool Application::RunApplication()
{
	// NOTE: This is the main application loop the user will be able to hook into
	// NOTE: the loop and define custom logic therein. The start should handle all
	// NOTE: subsystem management and initialisation.

	// NOTE: This is the actual game loop, the message queue is read
	// NOTE: and events distributed, any actual live logic is held within 


	while (m_ShouldRun)
	{
		if (!m_Platform.ReadMessageQueue())
		{ 
			ICS_INFO("Application: Read Messages break");
			m_ShouldRun = false;
		}
		if (m_ShouldPause) 
		{ 
			continue; 
		}
		if (!Update(m_Clock.time))
		{
			ICS_ERROR("Application: Could not find user defined update logic")
		}
		for (Layer* layer : m_Layers.GetLayerStack())
		{
			layer->OnRenderUpdate(m_Clock.time);
		}
		
		m_Clock.OnUpdate();
		m_Platform.GetEventHandler().DistributeKeyEventsToListeners();
	}


	// NOTE: This is the end of the application life, all deallocations
	// NOTE: and destructors should be called below. Or can be handled
	// NOTE: within the application destructor and called explicitly here...

	return true;
}

bool Application::ReactToEvent(KeyEvents::Event key_event, unsigned int EventIndex)
{
	switch (EventIndex)
	{
	case static_cast<char>(EventListener::EventTypes::ICS_APPLICATION_QUIT):
		ICS_INFO("Application: Event %s fired", EventListener::Strings[EventIndex]);
		m_ShouldRun = false;
		break;
	case static_cast<char>(EventListener::EventTypes::ICS_MEMORY_QUERY_ALLOC):
		if (key_event.KeyIsDown())
		{
			ICS_DEBUG(MemoryStats::GetMemoryAllocations());
		}
		break;
	}
	return true;
}

bool Application::ReactToEvent(MouseEvents::Event mouse_event, unsigned int EventIndex)
{
	return true;
}

bool Application::ReactToEvent(StateEvents::Event state_event, unsigned int EventIndex)
{
	return true;
}

