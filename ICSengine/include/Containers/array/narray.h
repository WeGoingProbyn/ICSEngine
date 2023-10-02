#pragma once

#include "Defines.h"
#include "Core/Memory/Memory.h"

template<typename T>
class narray
{
public:
	class Iterator {
	public:
		Iterator(narray<T>& arr, unsigned int start = 0) : narrayRef(arr), index(start) {}
	
		// Define iterator operations
		void operator++() { index++; }
		T& operator*() { return narrayRef[index]; }
		bool operator!=(const Iterator& other) const { return index != other.index; }
	private:
		narray<T>& narrayRef;
		unsigned int index;
	};
	
	// Functions to get iterators
	Iterator begin() {
		return Iterator(*this);
	}
	
	Iterator end() {
		return Iterator(*this, m_Size);
	}

public:
	template<typename... Types>
	narray(Types... args);

	narray();
	~narray();
	narray(MemoryType type);
	narray(unsigned int size);
	narray(unsigned int size, MemoryType type);
	narray(const narray& arr);
	narray(narray&& arr) noexcept;
	narray& operator=(const narray& arr);
	narray& operator=(narray&& arr) noexcept;
	
	T& operator[] (unsigned int index);
	bool operator== (const narray<T>& rhs);
	bool operator!= (const narray<T>& rhs);
	const T& operator[] (unsigned int index) const;

	void PopAtEnd();
	void PopAtStart();
	void PushToEnd(T in);
	void PushToStart(T in);
	void PopAt(unsigned int index);
	void PushAt(T in, unsigned int index);

	char* GetArrayPrintable();
	inline T* GetRawPointer() { return m_Ptr; }
	inline unsigned int Size() { return m_Size; }
	inline unsigned int Last() { return m_Size - 1; }
	inline unsigned int Allocated() { return m_AllocatedSize; }

	void Reverse();

protected:
	T* m_Ptr;
	MemoryType m_Tag;
	unsigned int m_Size;
	unsigned int m_Stride;
	unsigned int m_AllocatedSize;
};

#include "narray.inl"

