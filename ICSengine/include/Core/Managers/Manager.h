#pragma once

#include "Containers/Structures/HashMap.h"

template<typename Value>
class Manager
{
public:
	Manager() 
	:
	m_AssetStack(MemoryType::ICS_STACK_MANAGER)
	{
	}

	void PushToStack(String&& name);
	template<typename... Args>
	void PushToStack(String&& name, Args... args);
private:
	HashMap<String, Value> m_AssetStack;
};

template<typename Value>
void Manager<Value>::PushToStack(String&& name)
{
	Value* tmp = Memory::AllocateMemory<Value>(1u, MemoryType::ICS_STACK_MANAGER);
	m_AssetStack.Insert(name, *tmp);
}

template<typename Value>
template<typename... Args>
void Manager<Value>::PushToStack(String&& name, Args... args)
{
	Value* tmp = Memory::AllocateWithCstrctArgs<Value>(1u, MemoryType::ICS_STACK_MANAGER, args...);
	m_AssetStack.Insert(name, *tmp);
}