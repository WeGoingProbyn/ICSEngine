#pragma once

#include <Defines.h>
#include <Core/Memory/Memory.h>
#include <Core/Debugger/Logger.h>
#include <Core/Events/EventHandler.h>

#include "Application/UserInterface.h"

#ifdef ICS_PLATFORM_WINDOWS
#include "Platform/PlatformWin32.h"
#include "Graphics/DirectX11/RenderDirectX11.h"
#endif

class Application : public EventListener
{
public:
	ICS_API Application();
	ICS_API ~Application();
	ICS_API bool RunApplication(UserInterface& logic);

	inline bool ShouldRun() { return m_ShouldRun; }
	inline bool ShouldPause() { return m_ShouldPause; }

	virtual bool ReactToEvent(KeyEvents::Event key_event, unsigned int EventIndex);
	virtual bool ReactToEvent(MouseEvents::Event mouse_event, unsigned int EventIndex);
	virtual bool ReactToEvent(StateEvents::Event state_event, unsigned int EventIndex);
private:
	bool m_ShouldRun;
	bool m_ShouldPause;
	bool m_Initialised;

	Memory m_Memory;

#ifdef ICS_PLATFORM_WINDOWS
	PlatformWin32 m_Platform;
	RenderDirectX11 m_Render;
#endif
};