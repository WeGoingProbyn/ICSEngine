#pragma once

#include "Defines.h"

#include "Containers/array/darray.h"

class StateEvents {
public:
	class Event {
	public:
		enum struct Type {
			WindowResize,
			Invalid
		};
	private:
		int m_WidthPass;
		int m_HeightPass;
		Event::Type m_Type;

	public:
		Event() : m_Type(Type::Invalid), m_WidthPass(0), m_HeightPass(0) {}
		Event(Type type, int width, int height) : m_Type(type), m_WidthPass(width), m_HeightPass(height) {}

		inline bool StateIsResize() const { return m_Type == Type::WindowResize; }
		inline int GetWidthPass() const { return m_WidthPass; }
		inline int GetHeightPass() const { return m_HeightPass; }
	};
public:
	StateEvents();
	~StateEvents();
	StateEvents(const StateEvents& rhs);
	StateEvents(const StateEvents&& rhs) noexcept;
	StateEvents& operator=(const StateEvents& rhs);
	StateEvents& operator=(const StateEvents&& rhs) noexcept;

	void TrimBuffer();
	Event GetStateEvent();
	void AddStateEventToQueue(Event input);
	inline void Flush() { m_StateEventBuffer = darray<Event>(); }
private:
	darray<Event> m_StateEventBuffer;
};

