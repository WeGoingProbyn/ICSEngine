#include "Core/Events/KeyEvents.h"
#include "Core/Debugger/Logger.h"

KeyEvents::KeyEvents()
	:
	m_KeyEventBuffer(),
	m_KeyStates(narray<bool>(static_cast<unsigned int>(ICS_KeyCodes::KEYS_MAX_KEYS)))
{
}

bool KeyEvents::KeyIsPressed(unsigned char keycode) { return m_KeyStates[keycode]; }

bool KeyEvents::KeyQueueIsEmpty() { return m_KeyEventBuffer.Size() == 0; }

KeyEvents::Event KeyEvents::GetKeyEvent() { 
	if (m_KeyEventBuffer.Size() > 0u) {
		KeyEvents::Event event = m_KeyEventBuffer[0u];
		m_KeyEventBuffer.PopAt(0u);
		return event;
	}
	else { return KeyEvents::Event(KeyEvents::Event::Type::Invalid, ICS_KeyCodes::KEYS_MAX_KEYS); }
}
void KeyEvents::FlushKeyQueue() { 
	if (m_KeyStates.Size() > 0 && &m_KeyStates[0] != nullptr)
	{
		Memory::ZeroMemoryBlock(&m_KeyStates[0], sizeof(bool) * m_KeyStates.Size());
	}
	if (m_KeyEventBuffer.Size() > 0 && &m_KeyEventBuffer[0] != nullptr)
	{
		m_KeyEventBuffer.Resize(1);
		Memory::ZeroMemoryBlock(&m_KeyEventBuffer[0], sizeof(Event) * m_KeyEventBuffer.Size());
	}
	ICS_TRACE("Key Queue flushed...")
}

void KeyEvents::OnKeyUp(unsigned char keycode) 
{
	if (m_KeyStates[keycode]) 
	{
		m_KeyStates[keycode] = false;
		m_KeyEventBuffer.PushToEnd(KeyEvents::Event(KeyEvents::Event::Type::KeyUp, static_cast<ICS_KeyCodes>(keycode)));
		TrimEvents(m_KeyEventBuffer);
	}
}

void KeyEvents::OnKeyDown(unsigned char keycode) 
{
	if (!m_KeyStates[keycode])
	{
		m_KeyStates[keycode] = true;
		m_KeyEventBuffer.PushToEnd(KeyEvents::Event(KeyEvents::Event::Type::KeyDown, static_cast<ICS_KeyCodes>(keycode)));
		TrimEvents(m_KeyEventBuffer);
	}
}

template<typename T>
void KeyEvents::TrimEvents(darray<T>& buffer) {
	unsigned int size = 16u;
	if (buffer.Size() > size)
	{
		while (buffer.Size() > size)
		{
			buffer.PopAt(0u);
		}
		ICS_TRACE("Key Events trimmed...")
	}
}

void KeyEvents::PushEventToQueue(Event input) {
	m_KeyEventBuffer.PushToEnd(input);
	TrimEvents(m_KeyEventBuffer);
}