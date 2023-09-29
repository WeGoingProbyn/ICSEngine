#pragma once

#include "Core/Debugger/Logger.h"
#include "Containers/array/narray.h"
#include "Containers/String/String.h"

#include <type_traits>

template<typename T>
narray<T>::narray()
{
	m_Size = 0u;
	m_Ptr = nullptr;
	m_Stride = sizeof(T);
	m_AllocatedSize = m_Size;

	m_Tag = MemoryType::ICS_ARRAY;
}

template<typename T>
narray<T>::narray(unsigned int size)
{
	m_Size = size;
	m_Stride = sizeof(T);
	m_AllocatedSize = m_Size;
	m_Tag = MemoryType::ICS_ARRAY;
	m_Ptr = Memory::AllocateMemory<T>(m_AllocatedSize, m_Tag);
	if (m_Ptr == nullptr) { ICS_ERROR("narray: Allocated pointer returned as nullptr"); }
}

template<typename T>
narray<T>::narray(unsigned int size, MemoryType type)
{
	m_Tag = type;
	m_Size = size;
	m_Stride = sizeof(T);
	m_AllocatedSize = m_Size;
	m_Ptr = Memory::AllocateMemory<T>(m_AllocatedSize, m_Tag);
	if (m_Ptr == nullptr) { ICS_ERROR("narray: Allocated pointer returned as nullptr"); }
}

template<typename T>
narray<T>::narray(MemoryType type)
{
	m_Size = 0u;
	m_Tag = type;
	m_Ptr = nullptr;
	m_Stride = sizeof(T);
	m_AllocatedSize = m_Size;
}

template<typename T>
template<typename... Types>
narray<T>::narray(Types... args)
{
	m_Stride = sizeof(T);
	m_Size = sizeof...(Types);
	m_AllocatedSize = m_Size;
	if (m_Tag == MemoryType::UNKNOWN) { m_Tag = MemoryType::ICS_ARRAY; }
	m_Ptr = Memory::AllocateMemory<T>(m_AllocatedSize, m_Tag);
	unsigned int index = 0;
	((m_Ptr[index++] = static_cast<T>(args)), ...);

}

template<typename T>
narray<T>::~narray()
{
	if (m_Ptr)
	{
		if (Memory::FreeMemory(m_Ptr, m_AllocatedSize, m_Tag))
		{
			m_Size = 0;
			m_Stride = 0;
			m_Ptr = nullptr;
			m_AllocatedSize = 0;
		}
		else
		{
			ICS_ERROR("narray: Could not free memory on destruction");
		}
	}
	else
	{
		//ICS_TRACE("narray: Memory was initialised as nullptr or has been destructed already");
	}
}

template<typename T>
narray<T>::narray(const narray& arr)
{
	// Copy constructor, no need to destroy the copied.
	if (arr.m_Size == 0 || arr.m_Ptr == nullptr) 
	{ 
		m_Size = 0;
		m_Stride = 0;
		m_Ptr = nullptr;
		m_AllocatedSize = 0;
		m_Tag = arr.m_Tag;
	}
	else
	{
		m_Tag = arr.m_Tag;
		m_Size = arr.m_Size;
		m_Stride = arr.m_Stride;
		m_AllocatedSize = arr.m_AllocatedSize;
		m_Ptr = Memory::AllocateMemory<T>(arr.m_AllocatedSize, m_Tag);
		if (!Memory::DeepCopyMemoryBlock(m_Ptr, arr.m_Ptr, arr.m_AllocatedSize))
		{
			ICS_ERROR("narray: Could not copy memory on narray& copy construction");
			Memory::FreeMemory(arr.m_Ptr, arr.m_AllocatedSize, m_Tag);
			m_Ptr = nullptr;
		}
	}
}

template<typename T>
narray<T>::narray(narray&& arr) noexcept
{
	m_Tag = arr.m_Tag;
	m_Ptr = arr.m_Ptr;
	m_Size = arr.m_Size;
	m_Stride = arr.m_Stride;
	m_AllocatedSize = arr.m_AllocatedSize;

	arr.m_Size = 0;
	arr.m_Stride = 0;
	arr.m_Ptr = nullptr;
	arr.m_AllocatedSize = 0;
}

template<typename T>
narray<T>& narray<T>::operator=(const narray& arr)
{
	// Make sure we're not assigning ourselves
	if (this != &arr)
	{
		if (arr.m_Ptr == nullptr)
		{
			m_Ptr = nullptr;
			m_Tag = arr.m_Tag;
			m_Size = arr.m_Size;
			m_Stride = arr.m_Stride;
			m_AllocatedSize = arr.m_AllocatedSize;
		}

		else if (m_Ptr != nullptr)
		{
			// Can only deep copy if sizes are equal
			if (m_AllocatedSize == arr.m_AllocatedSize)
			{
				if (!Memory::DeepCopyMemoryBlock(m_Ptr, arr.m_Ptr, arr.m_AllocatedSize))
				{
					ICS_ERROR("narray: Could not copy memory on copy assignment");
				}
			}
			else
			{
				m_Tag = arr.m_Tag;
				m_Size = arr.m_Size;
				m_Stride = arr.m_Stride;
				m_AllocatedSize = arr.m_AllocatedSize;
				Memory::FreeMemory(m_Ptr, m_AllocatedSize, m_Tag);
				m_Ptr = Memory::AllocateMemory<T>(m_AllocatedSize, m_Tag);
				Memory::DeepCopyMemoryBlock(m_Ptr, arr.m_Ptr, m_AllocatedSize);
			}
		}
		else if (m_Ptr == nullptr)
		{
			m_Tag = arr.m_Tag;
			m_Size = arr.m_Size;
			m_Stride = arr.m_Stride;
			m_AllocatedSize = arr.m_AllocatedSize;
			m_Ptr = Memory::AllocateMemory<T>(m_AllocatedSize, m_Tag);

			if (m_Ptr == nullptr)
			{
				ICS_WARN("narray: Allocated pointer returned nullptr on copy assignment");
			}
			else if (!Memory::DeepCopyMemoryBlock(m_Ptr, arr.m_Ptr, arr.m_AllocatedSize))
			{
				ICS_ERROR("narray: Could not copy memory on copy assignment");
				Memory::FreeMemory(m_Ptr, m_AllocatedSize, m_Tag);
				m_Ptr = nullptr;
			}
		}
	}

	else
	{
		ICS_WARN("narray: Trying to deep copy a an object to itself");
	}
	return *this;
}

template<typename T>
narray<T>& narray<T>::operator=(narray&& arr) noexcept
{
	m_Tag = arr.m_Tag;
	m_Ptr = arr.m_Ptr;
	m_Size = arr.m_Size;
	m_Stride = arr.m_Stride;
	m_AllocatedSize = arr.m_AllocatedSize;

	arr.m_Size = 0;
	arr.m_Stride = 0;
	arr.m_Ptr = nullptr;
	arr.m_AllocatedSize = 0;
	return *this;
}

template<typename T>
bool narray<T>::operator== (const narray<T>& rhs)
{
	if (m_Size != rhs.m_Size || m_AllocatedSize != rhs.m_AllocatedSize || m_Stride != rhs.m_Stride)
	{
		return false;
	}
	else
	{
		for (unsigned int index = 0; index < Last(); index++)
		{
			if (m_Ptr[index] != rhs.m_Ptr[index])
			{
				return false;
			}
		}
		return true;
	}
}

template<typename T>
bool narray<T>::operator!= (const narray<T>& rhs)
{
	if (m_Size != rhs.m_Size || m_AllocatedSize != rhs.m_AllocatedSize || m_Stride != rhs.m_Stride)
	{
		return true;
	}
	else
	{
		for (unsigned int index = 0; index < Last(); index++)
		{
			if (m_Ptr[index] != rhs.m_Ptr[index])
			{
				return true;
			}
		}
		return false;
	}
}


template<typename T>
T& narray<T>::operator[] (unsigned int index)
{
	ICS_ASSERT_MSG(index < m_Size && m_Ptr != nullptr, "narray: Trying to access non-existant element");
	return m_Ptr[index];
}

template<typename T>
const T& narray<T>::operator[] (unsigned int index) const 
{ 
	return this[index];
}

template<typename T>
void narray<T>::PushAt(T in, unsigned int index)
{
	if (index > m_Size - 1) { ICS_ERROR("narray: Trying to push element %i beyond defined array size of %i", index, m_Size); return; }
	if (m_Ptr == nullptr) { ICS_ERROR("narray: Trying to push at index: %i, using a nullptr", index); return; }
	else { m_Ptr[index] = in; }
}

template<typename T>
void narray<T>::PopAt(unsigned int index)
{
	if (m_Ptr == nullptr) { ICS_ERROR("narray: Trying to pop at %i using a nullptr", index); return; }
	else if (index > m_Size - 1) { ICS_ERROR("narray: Trying to reset element %i beyond defined array size of %i", index, m_Size); return; }
	else { m_Ptr[index] = T(); }
}

template<typename T>
void narray<T>::PopAtEnd() 
{
	if (m_Ptr == nullptr) { ICS_ERROR("narray: Trying to pop last element in a nullptr"); }
	else { m_Ptr[m_Size - 1] = T(); }
}

template<typename T>
void narray<T>::PopAtStart()
{
	if (m_Ptr == nullptr) { ICS_ERROR("narry: Trying to pop first element in a nullptr"); }
	else { m_Ptr[0] = T(); }
}

template<typename T>
void narray<T>::PushToEnd(T in)
{
	if (m_Ptr == nullptr) { ICS_ERROR("narry: Trying to push last element in a nullptr"); }
	else { m_Ptr[m_Size - 1] = in; }
}

template<typename T>
void narray<T>::PushToStart(T in)
{
	if (m_Ptr == nullptr) { ICS_ERROR("narry: Trying to push first element in a nullptr"); }
	else { m_Ptr[0] = in; }
}

template<typename T>
char* narray<T>::GetArrayPrintable()
{
	const unsigned int buffmax = 6000u;
	char buff[buffmax] = "[ ";
	unsigned int length = (unsigned int)strlen(buff);
	if (m_Ptr == nullptr) { ICS_ERROR("narray: Trying to print non existant array"); }
	else {
		for (unsigned int index = 0; index < m_Size; index++)
		{
			if (index > 0 && ((index) % 3) == 0) { length += snprintf(buff + length, buffmax, "\n\t   "); }
			length += snprintf(buff + length, buffmax, "(%f, %i),", (float)m_Ptr[index], index);
		}
		buff[length - 1] = ' ';
		length += snprintf(buff + length, buffmax, "]");
	}
	// TODO: Change this to use the String container
	return _strdup(buff);
}
