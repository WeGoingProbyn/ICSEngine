#pragma once

#include "Containers/Structures/HashMap.h"

template<typename Value>
class Manager
{
public:
	Manager() 
		:
		m_Stack(MemoryType::ICS_STACK_MANAGER)
	{
	}

	~Manager()
	{
		for (String& key : m_Stack.GetLiveKeys())
		{
			Memory::FreeMemory(m_Stack[std::move(key)], 1u, MemoryType::ICS_STACK_MANAGER);
		}
	}

	Value& operator[](String&& key);

	void PushToStack(String&& name);
	template<typename... Args>
	void PushToStack(String&& name, Args... args);
private:
	HashMap<String, Value*> m_Stack;
};

template<typename Value>
Value& Manager<Value>::operator[](String&& key)
{
	return *m_Stack[std::move(key)];
}

template<typename Value>
void Manager<Value>::PushToStack(String&& name)
{
	Value* ptr = Memory::AllocateMemory<Value>(1u, MemoryType::ICS_STACK_MANAGER);
	m_Stack.Insert(name, ptr);
}

template<typename Value>
template<typename... Args>
void Manager<Value>::PushToStack(String&& name, Args... args)
{
	Value* ptr = Memory::AllocateWithCstrctArgs<Value>(1u, MemoryType::ICS_STACK_MANAGER, args...);
	m_Stack.Insert(name, ptr);
}