#include "Core/Events/EventListener.h"

EventListener::EventListener()
	:
	m_ActiveKeys(),
	m_ActiveEvents()
{
}

EventListener::~EventListener()
{
}

bool EventListener::operator==(const EventListener& rhs)
{
	if (m_ActiveEvents == rhs.m_ActiveEvents)
	{
		if (m_ActiveKeys == rhs.m_ActiveKeys)
		{
			return true;
		}
	}
	return false;
}

bool EventListener::UnRegisterEvent(EventListener::EventTypes type)
{
	// TODO: This should maybe warrant an unordered map implementation no?...
	for (unsigned int index = 0; index < m_ActiveEvents.Size(); index++)
	{
		if (m_ActiveEvents[index] == type)
		{
			m_ActiveKeys.PopAt(index);
			m_ActiveEvents.PopAt(index);
			return true;
		}
	}
	return false;
}

bool EventListener::RegisterKeyToEvent(EventListener::EventTypes type, ICS_KeyCodes code)
{
	for (unsigned int index = 0; index < m_ActiveEvents.Size(); index++)
	{
		if (m_ActiveEvents[index] == type)
		{

			// TODO: This shit is a bit annoying. My only theory (at 2:30am after Friday close),
			//		is some weird interaction between the nested darray when trying to call function
			//		from the indexed version of the base darray. Taking a copy and performing the
			//		relevant operations then again copying back into the nested darray. This is far
			//		from ideal and maybe the narray class needs to add logic to consider retreiving
			//		a copy of itself... I'm really not too sure... This is inefficient, but it works for now!
			auto test = m_ActiveKeys[index];
			test.PushToEnd(code);
			m_ActiveKeys[index].Resize(test.Size());
			m_ActiveKeys[index] = test;
			return true;
		}
	}
	ICS_WARN("EventListener: Trying to register to key code to an inactive event");
	return RegisterEvent(type, code);
}

bool EventListener::UnRegisterKeyToEvent(EventListener::EventTypes type, ICS_KeyCodes code)
{
	for (unsigned int index = 0; index < m_ActiveEvents.Size(); index++)
	{
		if (m_ActiveEvents[index] == type)
		{
			m_ActiveKeys.PopAt(index);
			m_ActiveEvents.PopAt(index);
			return true;
		}
	}
	return false;
}