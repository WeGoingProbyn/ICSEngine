#include "Core/Events/StateEvents.h"
#include "Core/Debugger/Logger.h"

StateEvents::StateEvents()
	:
	m_StateEventBuffer(darray<Event>())
{
}

StateEvents::~StateEvents()
{
}

StateEvents::StateEvents(const StateEvents& rhs)
	:
	m_StateEventBuffer(rhs.m_StateEventBuffer)
{
}

StateEvents::StateEvents(const StateEvents&& rhs) noexcept
	:
	m_StateEventBuffer(rhs.m_StateEventBuffer)
{
}

StateEvents& StateEvents::operator=(const StateEvents& rhs)
{
	if (this != &rhs)
	{
		m_StateEventBuffer = rhs.m_StateEventBuffer;
	}
	return *this;
}

StateEvents& StateEvents::operator=(const StateEvents&& rhs) noexcept
{
	if (this != &rhs)
	{
		m_StateEventBuffer = rhs.m_StateEventBuffer;
	}
	return *this;
}

void StateEvents::TrimBuffer() {
	if (m_StateEventBuffer.Size() > 16u)
	{
		while (m_StateEventBuffer.Size() > 16u) {
				m_StateEventBuffer.PopAtStart();
		}
		ICS_TRACE("State Events trimmed...")
	}
}

void StateEvents::AddStateEventToQueue(StateEvents::Event input) {
	m_StateEventBuffer.PushToEnd(input);
	TrimBuffer();
	ICS_TRACE("Window state change detected")
}

StateEvents::Event StateEvents::GetStateEvent() {
	if (m_StateEventBuffer.Size() > 0u) {
		StateEvents::Event out = m_StateEventBuffer[0];
		m_StateEventBuffer.PopAtStart();
		return out;
	}
	else { return StateEvents::Event(StateEvents::Event::Type::Invalid, 0, 0); }
}