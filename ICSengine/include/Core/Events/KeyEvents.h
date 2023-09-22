#pragma once

#include "Containers/array/darray.h"

#include "Defines.h"
#include "Core/Events/KeyDefines.h"

class KeyEvents {
public:
	class Event {
	public:
		enum struct Type {
			KeyUp,
			KeyDown,
			KeyReset,
			Invalid
		};

	public:
		Event() : m_Type(Type::Invalid), m_KeyCode(ICS_KeyCodes::KEYS_MAX_KEYS) {}
		Event(Type type, ICS_KeyCodes keycode) : m_Type(type), m_KeyCode(keycode) {}
		inline bool KeyIsUp() const { return m_Type == Type::KeyUp; }
		inline bool KeyIsDown() const { return m_Type == Type::KeyDown; }
		inline bool KeyIsReset() const { return m_Type == Type::KeyReset; }
		inline ICS_KeyCodes GetKeyCode() const { return m_KeyCode; }

	private:
		Type m_Type;
		ICS_KeyCodes m_KeyCode;
	};
public:
	KeyEvents();

	ICS_API bool KeyIsPressed(unsigned char keycode);
	ICS_API bool KeyQueueIsEmpty();
	ICS_API Event GetKeyEvent();
	ICS_API void FlushKeyQueue();
	ICS_API void PushEventToQueue(Event input);
	ICS_API void OnKeyUp(unsigned char keycode);
	ICS_API void OnKeyDown(unsigned char keycode);

	inline darray<Event>& GetKeyEventBuffer() { return m_KeyEventBuffer; }
private:
	template<typename T>
	static void TrimEvents(darray<T>& buffer);

	// Maybe the keystates aren't needed. Handle all important
	// inputs with the buffer so that the keystroke isnt missed
	// during a given iteration within the game loop, make buffer 
	// bigger before trim occurs to balance loss of state info...
	// 
	// Keeping keystates around may be useful for debugging...
	// maybe reprofile this part when the library becomes more serious.


	narray<bool> m_KeyStates;
	darray<Event> m_KeyEventBuffer;
};
