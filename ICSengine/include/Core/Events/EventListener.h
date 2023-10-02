#pragma once

#include "Defines.h"
#include "Core/Events/KeyDefines.h"
#include "Containers/array/darray.h"

#include "Core/Events/KeyEvents.h"
#include "Core/Events/MouseEvents.h"
#include "Core/Events/StateEvents.h"

class EventListener
{
public:
	enum struct EventTypes
	{
		ICS_APPLICATION_QUIT,
		ICS_MEMORY_QUERY_ALLOC,
		ICS_PLATFORM_STATE_CHANGE,
		ICS_EVENT_TYPES_MAX
	};

	const char* Strings[static_cast<unsigned int>(EventListener::EventTypes::ICS_EVENT_TYPES_MAX)] = {
		"ICS_APPLICATION_QUIT",
		"ICS_MEMORY_QUERY_ALLOC",
		"ICS_PLATFORM_STATE_CHANGE",
	};
public:
	ICS_API EventListener();
	ICS_API virtual ~EventListener() = 0;
	bool operator==(const EventListener& rhs);

	template<typename... Types>
	EventListener(EventListener::EventTypes type, Types... args);
	template<typename... Types>
	bool RegisterEvent(EventListener::EventTypes type, Types... args);
	
	ICS_API bool UnRegisterEvent(EventTypes type);
	ICS_API bool RegisterKeyToEvent(EventTypes type, ICS_KeyCodes code);
	ICS_API bool UnRegisterKeyToEvent(EventTypes type, ICS_KeyCodes code);

	ICS_API virtual inline bool ReactToEvent(KeyEvents::Event key_event, unsigned int EventIndex) { return false; }
	ICS_API virtual inline bool ReactToEvent(MouseEvents::Event mouse_event, unsigned int EventIndex) { return false; }
	ICS_API virtual inline bool ReactToEvent(StateEvents::Event state_event, unsigned int EventIndex) { return false; }

	darray<darray<ICS_KeyCodes>>& GetActiveKeys() { return m_ActiveKeys; }
	darray<EventListener::EventTypes>& GetActiveEvents() { return m_ActiveEvents; }
protected:
	darray<darray<ICS_KeyCodes>> m_ActiveKeys;
	darray<EventListener::EventTypes> m_ActiveEvents;
};

template<typename... Types>
EventListener::EventListener(EventListener::EventTypes type, Types... args)
	:
	EventListener()
{
	RegisterEvent(type, args...);
}

template<typename... Types>
bool EventListener::RegisterEvent(EventListener::EventTypes type, Types... args)
{
	m_ActiveEvents.PushToEnd(type);
	m_ActiveKeys.PushToEnd({ args... });
	return true;
}