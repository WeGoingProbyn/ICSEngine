#pragma once

#include "Core/Events/KeyEvents.h"
#include "Core/Events/MouseEvents.h"
#include "Core/Events/StateEvents.h"
#include "Core/Events/EventListener.h"

class EventHandler
{
public:
	ICS_API EventHandler();
	ICS_API ~EventHandler();
	
	ICS_API inline KeyEvents& GetKeyEvents() { return m_KeyEvents; }
	ICS_API inline MouseEvents& GetMouseEvents() { return m_MouseEvents; }
	ICS_API inline StateEvents& GetStateEvents() { return m_StateEvents; }

	ICS_API bool DistributeKeyEventsToListeners();
	//bool DistributeMouseEventsToListeners();
	//bool DistributeStateEventsToListeners();
	ICS_API bool RegisterListener(EventListener& listener);
	ICS_API bool UnRegisterListener(EventListener& listener);
private:
	KeyEvents m_KeyEvents;
	StateEvents m_StateEvents;
	MouseEvents m_MouseEvents;
	darray<EventListener*> m_Listeners;
};