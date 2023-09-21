#pragma once

#include "Core/Events/KeyEvents.h"
#include "Core/Events/MouseEvents.h"
#include "Core/Events/StateEvents.h"
#include "Core/Events/EventListener.h"

class EventHandler
{
public:
	EventHandler();
	~EventHandler();
	
	inline KeyEvents& GetKeyEvents() { return m_KeyEvents; }
	inline MouseEvents& GetMouseEvents() { return m_MouseEvents; }
	inline StateEvents& GetStateEvents() { return m_StateEvents; }

	bool DistributeKeyEventsToListeners();
	//bool DistributeMouseEventsToListeners();
	//bool DistributeStateEventsToListeners();
	bool RegisterListener(EventListener& listener);
	bool UnRegisterListener(EventListener& listener);
private:
	KeyEvents m_KeyEvents;
	StateEvents m_StateEvents;
	MouseEvents m_MouseEvents;
	darray<EventListener*> m_Listeners;
};