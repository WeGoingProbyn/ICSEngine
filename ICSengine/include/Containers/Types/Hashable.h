#pragma once

// include here so derived
// doesn't need to always include
#include <iostream>

class Hashable
{
public:
	inline Hashable() : m_HashValue(0) {}
	inline unsigned int GetHashValue() { return m_HashValue; }
protected:
	virtual void Hash() = 0;
protected:
	unsigned int m_HashValue;
};

