#include "Core/Events/MouseEvents.h"
#include "Core/Debugger/Logger.h"

// TODO: This is annoying
#include <windows.h>

MouseEvents::MouseEvents()
	:
	m_MouseMoveBuffer(darray<Event>()),
	m_MouseEventBuffer(darray<Event>())
{
	m_MouseButtons[0] = false;
	m_MouseButtons[1] = false;
	m_MouseButtons[2] = false;
}

MouseEvents::~MouseEvents()
{
}

MouseEvents::MouseEvents(const MouseEvents& rhs)
	:
	m_MouseMoveBuffer(rhs.m_MouseMoveBuffer),
	m_MouseEventBuffer(rhs.m_MouseEventBuffer)
{
	m_MouseButtons[0] = false;
	m_MouseButtons[1] = false;
	m_MouseButtons[2] = false;
}

MouseEvents::MouseEvents(const MouseEvents&& rhs) noexcept
	:
	m_MouseMoveBuffer(rhs.m_MouseMoveBuffer),
	m_MouseEventBuffer(rhs.m_MouseEventBuffer)
{
	m_MouseButtons[0] = false;
	m_MouseButtons[1] = false;
	m_MouseButtons[2] = false;
}

MouseEvents& MouseEvents::operator=(const MouseEvents& rhs)
{
	if (this != &rhs)
	{
		m_MouseMoveBuffer = rhs.m_MouseMoveBuffer;
		m_MouseEventBuffer = rhs.m_MouseEventBuffer;

		m_MouseButtons[0] = false;
		m_MouseButtons[1] = false;
		m_MouseButtons[2] = false;
	}
	return *this;
}

MouseEvents& MouseEvents::operator=(const MouseEvents&& rhs) noexcept
{
	if (this != &rhs)
	{
		m_MouseMoveBuffer = rhs.m_MouseMoveBuffer;
		m_MouseEventBuffer = rhs.m_MouseEventBuffer;

		m_MouseButtons[0] = false;
		m_MouseButtons[1] = false;
		m_MouseButtons[2] = false;
	}
	return *this;
}

void MouseEvents::OnScrollDeltaChange(int delta) {
	m_WheelScrollDelta += delta;
	while (m_WheelScrollDelta >= WHEEL_DELTA) {
		m_WheelScrollDelta -= WHEEL_DELTA;
		OnScrollUp();
	}
	while (m_WheelScrollDelta <= -WHEEL_DELTA) {
		m_WheelScrollDelta += WHEEL_DELTA;
		OnScrollDown();
	}
}

void MouseEvents::OnMouseMoveEvent() {

	if (m_MouseMoveBuffer.Size() > 0 && (m_MouseMoveBuffer[m_MouseMoveBuffer.Last()].x == x || m_MouseMoveBuffer[m_MouseMoveBuffer.Last()].y == y))
	{
		return;
	}
	else
	{
		m_MouseMoveBuffer.PushToEnd(MouseEvents::Event(x, y, Event::Type::MouseMove, Event::Button::Invalid));
		//ICS_TRACE("Mouse Events: Mouse at position x: %i, y: %i", x, y);
		TrimMoveBuffer();
	}
}

void MouseEvents::OnScrollUp() {
	m_MouseEventBuffer.PushToEnd(MouseEvents::Event(x, y, Event::Type::ScrollUp, Event::Button::Middle));
	TrimEventBuffer();
}

void MouseEvents::OnScrollDown() {
	m_MouseEventBuffer.PushToEnd(MouseEvents::Event(x, y, Event::Type::ScrollDown, Event::Button::Middle));
	TrimEventBuffer();
}

void MouseEvents::OnLeftButtonUp() {
	m_MouseButtons[0] = false;
	m_MouseEventBuffer.PushToEnd(MouseEvents::Event(x, y, Event::Type::ButtonUp, Event::Button::Left));
	TrimEventBuffer();
}

void MouseEvents::OnLeftButtonDown() {
	m_MouseButtons[0] = true;
	m_MouseEventBuffer.PushToEnd(MouseEvents::Event(x, y, Event::Type::ButtonDown, Event::Button::Left));
	TrimEventBuffer();
}

void MouseEvents::OnRightButtonUp() {
	m_MouseButtons[1] = false;
	m_MouseEventBuffer.PushToEnd(MouseEvents::Event(x, y, Event::Type::ButtonUp, Event::Button::Right));
	TrimEventBuffer();
}

void MouseEvents::OnRightButtonDown() {
	m_MouseButtons[1] = true;
	m_MouseEventBuffer.PushToEnd(MouseEvents::Event(x, y, Event::Type::ButtonDown, Event::Button::Right));
	TrimEventBuffer();
}

void MouseEvents::OnMiddleButtonUp() {
	m_MouseButtons[2] = false;
	m_MouseEventBuffer.PushToEnd(MouseEvents::Event(x, y, Event::Type::ButtonUp, Event::Button::Middle));
	TrimEventBuffer();
}

void MouseEvents::OnMiddleButtonDown() {
	m_MouseButtons[2] = true;
	m_MouseEventBuffer.PushToEnd(MouseEvents::Event(x, y, Event::Type::ButtonDown, Event::Button::Middle));
	TrimEventBuffer();
}

void MouseEvents::TrimEventBuffer() {
	if (m_MouseEventBuffer.Size() > 16u)
	{
		while (m_MouseEventBuffer.Size() > 16u) {
			m_MouseEventBuffer.PopAtStart();
		}
		ICS_TRACE("Mouse Events trimmed...")
	}
}

void MouseEvents::TrimMoveBuffer() {
	if (m_MouseMoveBuffer.Size() > 16u)
	{
		while (m_MouseMoveBuffer.Size() > 16u) {
			m_MouseMoveBuffer.PopAtStart();
		}
		//ICS_TRACE("Move Events trimmed...")
	}
}

MouseEvents::Event MouseEvents::GetMoveEvent() {
	if (m_MouseMoveBuffer.Size() > 0u) {
		MouseEvents::Event event = m_MouseMoveBuffer[0];
		m_MouseMoveBuffer.PopAtStart();
		return event;
	}
	else { return MouseEvents::Event(0, 0, MouseEvents::Event::Type::Invalid, MouseEvents::Event::Button::Invalid); }
}

MouseEvents::Event MouseEvents::GetButtonEvent() {
	if (m_MouseEventBuffer.Size() > 0u) {
		MouseEvents::Event event = m_MouseEventBuffer[0];
		m_MouseEventBuffer.PopAtStart();
		return event;
	}
	else { return MouseEvents::Event(0, 0, MouseEvents::Event::Type::Invalid, MouseEvents::Event::Button::Invalid); }
}