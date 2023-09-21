#pragma once

#include "Containers/array/darray.h"

class MouseEvents {
public:
	class Event {
	public:
		enum struct Button {
			Left,
			Right,
			Middle,
			Invalid
		};

		enum struct Type {
			ButtonUp,
			ButtonDown,
			ScrollUp,
			ScrollDown,
			MouseMove,
			Invalid
		};

	public:
		int x;
		int y;

		Type m_Type;
		Button m_Button;
	public:
		Event() : x(0), y(0), m_Type(Type::Invalid), m_Button(Button::Invalid) {}
		Event(int x, int y, Type type, Button button) : x(x), y(y), m_Type(type), m_Button(button) {}
		
		inline bool ButtonIsLeft() const { return m_Button == Button::Left; }
		inline bool ButtonIsRight() const { return m_Button == Button::Right; }
		inline bool ButtonIsMiddle() const { return m_Button == Button::Middle; }

		inline bool ButtonIsUp() const { return m_Type == Type::ButtonUp; }
		inline bool ButtonIsDown() const { return m_Type == Type::ButtonDown; }
		inline bool ScrollingUp() const { return m_Type == Type::ScrollUp; }
		inline bool ScrollingDown() const { return m_Type == Type::ScrollDown; }
		inline bool MouseIsMoving() const { return m_Type == Type::MouseMove; }
	};
public:
	MouseEvents();
	~MouseEvents();
	MouseEvents(const MouseEvents& rhs);
	MouseEvents(const MouseEvents&& rhs) noexcept;
	MouseEvents& operator=(const MouseEvents& rhs);
	MouseEvents& operator=(const MouseEvents&& rhs) noexcept;

	Event GetMoveEvent();
	Event GetButtonEvent();
	
	inline int GetPositionX() const { return x; }
	inline int GetPositionY() const { return y; }
	inline void SetPositions(int _x, int _y) { x = _x; y = _y; }
	inline bool LeftButtonIsPressed() const { return m_MouseButtons[0]; }
	inline bool RightButtonIsPressed() const { return m_MouseButtons[1]; }
	inline bool MiddleButtonIsPressed() const { return m_MouseButtons[2]; }
	inline bool MouseQueueIsEmpty() { return m_MouseEventBuffer.Size() == 0; }
	inline void FlushMouseQueue() { m_MouseEventBuffer = darray<Event>(); }

	void OnScrollUp();
	void OnScrollDown();
	void OnLeftButtonUp();
	void TrimMoveBuffer();
	void TrimEventBuffer();
	void OnRightButtonUp();
	void OnMouseMoveEvent();
	void OnMiddleButtonUp();
	void OnLeftButtonDown();
	void OnRightButtonDown();
	void OnMiddleButtonDown();
	void OnScrollDeltaChange(int delta);

private:
	int x = 0;
	int y = 0;
	int m_WheelScrollDelta = 0;
	// 0 = left, 1 = right, 2 = middle
	bool m_MouseButtons[3];

	darray<Event> m_MouseMoveBuffer;
	darray<Event> m_MouseEventBuffer;
};
