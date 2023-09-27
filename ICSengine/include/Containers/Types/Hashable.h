#pragma once

#include "Core/Debugger/Logger.h"
#include "Containers/Spatial/Vector.h"

class HashableBase
{
public:
	HashableBase() : m_HashValue(0) {}
	inline virtual unsigned int GetHashValue() { return m_HashValue; }
protected:
	unsigned int m_HashValue;
};

// Generic Hashable Definition

template<typename T>
class Hashable : public HashableBase
{
public:
	Hashable(T& hashable)
		:
	m_HashValue(0)
	{
		ICS_WARN("Hashable: Object does not have a defined hash function");
	};
};

// Overrides for Generic Hashable definitions, used for non templated types

template<>
Hashable<String>::Hashable(String& hashable)
{
	// TODO: Remove the std string here, probably means doing manual hashing of chars
	std::string tmp = hashable.AsCstr();
	HashableBase::m_HashValue = (unsigned int)std::hash<std::string>{}(tmp);
}

// Typed required specialised hashable definitions

template<typename T, unsigned int dim>
class Hashable<Vector<T, dim>> : public HashableBase
{
public:
	Hashable(Vector<T, dim>& hashable)
	{
		for (T& val : hashable)
		{
			HashableBase::m_HashValue ^= std::hash<T>{}(val);
		}
	}
};
