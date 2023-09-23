#pragma once

#include <Defines.h>
#include <Core/Memory/Memory.h>
#include <Core/Debugger/Logger.h>
#include <Core/Events/EventHandler.h>

#include "Layers/LayerManager.h"

#ifdef ICS_PLATFORM_WINDOWS
#include "Platform/PlatformWin32.h"
#include "Graphics/DirectX11/RenderDirectX11.h"
#endif

class Application : public EventListener
{
public:
	ICS_API Application();
	ICS_API virtual ~Application();

	ICS_API bool RunApplication();
	inline LayerManager& GetLayers() { return m_Layers; }
	inline void RegisterListener(EventListener& listener) { m_Platform.GetEventHandler().RegisterListener(listener); }
private:
	ICS_API virtual bool ReactToEvent(KeyEvents::Event key_event, unsigned int EventIndex);
	ICS_API virtual bool ReactToEvent(MouseEvents::Event mouse_event, unsigned int EventIndex);
	ICS_API virtual bool ReactToEvent(StateEvents::Event state_event, unsigned int EventIndex);

	inline bool ShouldRun() { return m_ShouldRun; }
	inline bool ShouldPause() { return m_ShouldPause; }

	ICS_API virtual bool Update(float deltaTime) = 0;

private:
	bool m_ShouldRun;
	bool m_ShouldPause;
	
	Memory m_Memory;
	LayerManager m_Layers;

#ifdef ICS_PLATFORM_WINDOWS
	PlatformWin32 m_Platform;
	RenderDirectX11 m_Render;
#endif

};