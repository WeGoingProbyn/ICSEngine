#include "Core/Events/EventHandler.h"

EventHandler::EventHandler()
	:
	m_KeyEvents(),
	m_MouseEvents(),
	m_StateEvents(),
	m_Listeners()
{

}

EventHandler::~EventHandler()
{
}

bool EventHandler::DistributeKeyEventsToListeners()
{
	if (m_KeyEvents.GetKeyEventBuffer().Size() == 0) { return false; }
	for (unsigned int i = 0; i < m_KeyEvents.GetKeyEventBuffer().Size(); i++)
	{
 		KeyEvents::Event key_event = m_KeyEvents.GetKeyEvent();
		for (EventListener* listener : m_Listeners)
		{
			for (unsigned int index = 0; index < listener->GetActiveKeys().Size(); index++)
			{
				for (ICS_KeyCodes& key_code : listener->GetActiveKeys()[index])
				{
					if (key_code == key_event.GetKeyCode())
					{
						listener->ReactToEvent(key_event, index);
					}
				}
			}
		}
	}
	return true;
}

bool EventHandler::RegisterListener(EventListener& listener)
{
	m_Listeners.PushToEnd(&listener);
	return true;
}

bool EventHandler::UnRegisterListener(EventListener& listener)
{
	for (unsigned int index = 0; index < m_Listeners.Size(); index++)
	{
		if (m_Listeners[index] == &listener)
		{
			m_Listeners.PopAt(index);
			return true;
		}
	}
	return false;
}