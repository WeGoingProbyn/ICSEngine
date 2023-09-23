#pragma once

#include "Containers/array/narray.h"

template<typename T>
class darray : public narray<T>
{
public:
	template<typename... Types>
	darray(Types... args);

	darray();
	~darray();
	darray(MemoryType type);
	
	void Resize(unsigned int size);
	void PopAtEnd() ;
	void PopAtStart() ;
	void PushToEnd(T in) ;
	void PushToStart(T in) ;
	void PopAt(unsigned int index) ;
	void PushAt(T in, unsigned int index) ;
protected:
	float m_AllocatedFactor;
};

#include "darray.inl"