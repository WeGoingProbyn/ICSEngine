#include "Application/Application.h"

#include <Core/Debugger/Logger.h>
#include <Core/Managers/Manager.h>
#include <Core/Structures/Geometry/Square.h>

Application::Application() 
	:
	m_Render(m_Platform.GetConfig().width, m_Platform.GetConfig().height, m_Platform.GetPlatformHandle().InternalHandle)
{
	m_ShouldRun = true;
	m_ShouldPause = false;
	RegisterListener(reinterpret_cast<EventListener&>(*this));
	ICS_INFO("Application created");
}

Application::~Application() 
{
	m_ShouldRun = false;
	m_ShouldPause = false;
	ICS_INFO("Application destroyed");
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
		};
		if (m_ShouldPause) 
		{ 
			continue; 
		}
		if (!Update(0.0f)) 
		{
			ICS_ERROR("Application: Could not find user defined update logic")
		}

		m_Platform.GetEventHandler().DistributeKeyEventsToListeners();
		
		m_Render.BindBackBuffer();

		for (Layer* layer : m_Layers.GetLayerStack())
		{
			layer->OnRenderUpdate(m_Render);
		}

		m_Render.FlipFrameBuffers();
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

