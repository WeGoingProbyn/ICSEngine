#pragma once

#include "Containers/array/darray.h"
//#include <cmath>

template<typename T>
template<typename... Types>
darray<T>::darray(Types... args)
{
	m_AllocatedFactor = 0.5f;
	narray<T>::m_Stride = sizeof(T);
	narray<T>::m_Size = sizeof...(Types);
	narray<T>::m_Tag = MemoryType::ICS_DARRAY;
	narray<T>::m_AllocatedSize = narray<T>::m_Size;
	narray<T>::m_Ptr = Memory::AllocateMemory<T>(narray<T>::m_Size, narray<T>::m_Tag);

	unsigned int index = 0;
	((narray<T>::m_Ptr[index++] = static_cast<T>(args)), ...);
}

template<typename T>
darray<T>::darray()
	:
	m_AllocatedFactor(0.5f),
	narray<T>(MemoryType::ICS_DARRAY)
{
}

template<typename T>
darray<T>::darray(MemoryType type)
	:
	m_AllocatedFactor(0.5f),
	narray<T>(type)
{
}

template<typename T>
darray<T>::~darray() 
{
	m_AllocatedFactor = 0.0f;
}

template<typename T>
void darray<T>::Resize(unsigned int size)
{
	if (!narray<T>::m_Ptr)
	{
		narray<T>::m_Size = size;
		narray<T>::m_AllocatedSize = size;
		narray<T>::m_Ptr = Memory::AllocateMemory<T>(size, narray<T>::m_Tag);
		return;
	}

	if (size < narray<T>::m_Size)
	{
		ICS_WARN("narray: Resizing to %i, original size is %i, Contents will be clipped to refit", size, narray<T>::m_Size);
	}

	T* ptr = static_cast<T*>(Memory::AllocateMemory<T>(size, narray<T>::m_Tag));
	if (Memory::CopyMemoryBlock(ptr, narray<T>::m_Ptr, narray<T>::m_Size))
	{
		if (!Memory::FreeMemory(narray<T>::m_Ptr, narray<T>::m_AllocatedSize, narray<T>::m_Tag))
		{
			ICS_ERROR("narray: Could not free original memory on Resize");
		}
		else
		{
			narray<T>::m_Ptr = ptr;
			narray<T>::m_Size = size;
			narray<T>::m_AllocatedSize = size;
		}
	}
	else
	{
		ICS_ERROR("narray: Could not copy memory on Resize");
	}
}

template<typename T>
void darray<T>::PopAtEnd()
{
	if (narray<T>::m_Ptr == nullptr) { ICS_ERROR("darray: Trying to pop at end of nullptr") }
	else 
	{
		// Can just keep the popped memory around incase we need to use it again
		narray<T>::m_Ptr[narray<T>::m_Size - 1] = T();
		narray<T>::m_Size--;
	}
}

template<typename T>
void darray<T>::PopAtStart()
{
	if (narray<T>::m_Ptr == nullptr) { ICS_ERROR("darray: Trying to pop at start of nullptr") }
	// Should move everything down, can shuffle freed memory to the end
	else if (Memory::DeepCopyMemoryBlock(narray<T>::m_Ptr, narray<T>::m_Ptr + 1, narray<T>::m_Size - 1))
	{
		narray<T>::m_Size--;
	}
	else
	{
		ICS_WARN("darray: Could not pop at start of darray");
	}
}

template<typename T>
void darray<T>::PushToEnd(T in)
{
	if (narray<T>::m_Ptr == nullptr)
	{
		narray<T>::m_AllocatedSize = 1u;
		narray<T>::m_Ptr = Memory::AllocateMemory<T>(narray<T>::m_AllocatedSize, narray<T>::m_Tag);
	}
	else if (narray<T>::m_Size == narray<T>::m_AllocatedSize)
	{
		// Need to increase the size of the allocated memory
		narray<T>::m_AllocatedSize += (unsigned int)std::ceil(narray<T>::m_Size * m_AllocatedFactor);
		T* ptr = Memory::AllocateMemory<T>(narray<T>::m_AllocatedSize, narray<T>::m_Tag);
		if (Memory::DeepCopyMemoryBlock(ptr, narray<T>::m_Ptr, narray<T>::m_Size))
			if (Memory::FreeMemory(narray<T>::m_Ptr, narray<T>::m_Size, narray<T>::m_Tag))
			{
				narray<T>::m_Ptr = ptr;
			}
			else
			{
				ICS_ERROR("darray: Could not free original memory on size reallocation during push to emd");
				return;
			}
		
		
		else 
		{ 
			ICS_ERROR("darray: Could not copy original memory on size reallocation during push to emd"); 
			return; 
		}
	}

	narray<T>::m_Ptr[narray<T>::m_Size] = in;
	narray<T>::m_Size++;
}

template<typename T>
void darray<T>::PushToStart(T in)
{
	if (narray<T>::m_Ptr == nullptr)
	{
		narray<T>::m_AllocatedSize = 1u;
		narray<T>::m_Ptr = Memory::AllocateMemory<T>(narray<T>::m_AllocatedSize, narray<T>::m_Tag);
	}
	else if (narray<T>::m_Size == narray<T>::m_AllocatedSize)
	{
		// Need to increase the size of the allocated memory
		narray<T>::m_AllocatedSize += (unsigned int)std::ceil(narray<T>::m_Size * m_AllocatedFactor);
		T* ptr = Memory::AllocateMemory<T>(narray<T>::m_AllocatedSize, narray<T>::m_Tag);

		if (Memory::DeepCopyMemoryBlock(ptr + 1, narray<T>::m_Ptr, narray<T>::m_Size))
		{
			Memory::FreeMemory(narray<T>::m_Ptr, narray<T>::m_Size, narray<T>::m_Tag);
			narray<T>::m_Ptr = ptr;
		}
		else
		{
			ICS_ERROR("darray: Could not copy memory on size reallocation during push to start"); 
			return;
		}
	}
	else
	{
		if (!Memory::CopyMemoryBlock(narray<T>::m_Ptr + 1, narray<T>::m_Ptr, narray<T>::m_Size))
		{
			ICS_ERROR("darray: Could not copy memory during push to start");
			return;
		}
	}
	narray<T>::m_Size++;
	narray<T>::m_Ptr[0] = in;
}

template<typename T>
void darray<T>::PopAt(unsigned int index)
{
	if (narray<T>::m_Ptr == nullptr)
	{
		narray<T>::m_AllocatedSize = 1u;
		narray<T>::m_Ptr = Memory::AllocateMemory<T>(narray<T>::m_AllocatedSize, narray<T>::m_Tag);
	}
	else if (index > narray<T>::m_Size - 1) 
	{ 
		ICS_WARN("darray: Trying to pop non-existant element");
		return; 
	}
	else if (narray<T>::m_Size == 1)
	{
		Memory::FreeMemory(narray<T>::m_Ptr, 1u, narray<T>::m_Tag);
		narray<T>::m_Ptr = nullptr;
		narray<T>::m_Size--;
		narray<T>::m_AllocatedSize--;
		return;
	}

	if (Memory::DeepCopyMemoryBlock(narray<T>::m_Ptr + index, narray<T>::m_Ptr + index + 1, narray<T>::m_Size - index - 1))
	{
		narray<T>::m_Size--;
	}
	else
	{
		ICS_ERROR("darray: Could not pop at index: %i", index); 
		return;
	}
}

template<typename T>
void darray<T>::PushAt(T in, unsigned int index)
{
	if (narray<T>::m_Ptr == nullptr)
	{
		narray<T>::m_AllocatedSize = 1u;
		narray<T>::m_Ptr = Memory::AllocateMemory<T>(narray<T>::m_AllocatedSize, narray<T>::m_Tag);
	}

	if (index == 0) 
	{ 
		PushToStart(in);
		return; 
	}
	else if (index == narray<T>::m_Size) 
	{
		PushToEnd(in);
		return;
	}
	else if (index > narray<T>::m_AllocatedSize) 
	{
		ICS_WARN("darray: Trying to push an element past alocated block, pushed to end"); 
		PushToEnd(in);
		return;
	}
	else if (narray<T>::m_Size == narray<T>::m_AllocatedSize)
	{
		narray<T>::m_AllocatedSize += (unsigned int)std::ceil(narray<T>::m_Size * m_AllocatedFactor);
		T* ptr = Memory::AllocateMemory<T>(narray<T>::m_AllocatedSize, narray<T>::m_Tag);

		if (Memory::DeepCopyMemoryBlock(ptr, narray<T>::m_Ptr, narray<T>::m_Size - index))
		{
			if (Memory::DeepCopyMemoryBlock(ptr + index + 1, narray<T>::m_Ptr + index, narray<T>::m_Size - index))
			{
				if (Memory::FreeMemory(narray<T>::m_Ptr, narray<T>::m_Size, narray<T>::m_Tag))
				{
					narray<T>::m_Ptr = ptr;
				}
				else
				{
					ICS_ERROR("darray: Could not free original memory on size reallocation during push at index: %i", index);
					return;
				}
			}
			else
			{
				ICS_ERROR("darray: Could not copy memory to the right on size reallocation during push at index: %i", index);
				return;
			}
		}
		else
		{
			ICS_ERROR("darray: Could not copy memory to the left on size reallocation during push at index: %i", index); 
			return;
		}
	}
	else
	{
		if (Memory::DeepCopyMemoryBlock(narray<T>::m_Ptr, narray<T>::m_Ptr, (narray<T>::m_Size - index)))
		{
			if (Memory::DeepCopyMemoryBlock(narray<T>::m_Ptr + index + 1, narray<T>::m_Ptr + index, narray<T>::m_Size - index))
			{
				narray<T>::m_Ptr[index] = in;
				narray<T>::m_Size++;
			}
			else
			{
				ICS_ERROR("darray: Could not copy memory to the right during push at index: %i", index);
			}
		}
		else
		{
			ICS_ERROR("darray: Could not copy memory to the left during push at index: %i", index);
		}
	}
}

template<typename T>
void darray<T>::Flush()
{
	if (narray<T>::m_Ptr)
	{
		Memory::FreeMemory(narray<T>::m_Ptr, narray<T>::m_AllocatedSize, narray<T>::m_Tag);
		narray<T>::m_Ptr = nullptr;
		narray<T>::m_Size = 0u;
		narray<T>::m_AllocatedSize = 0u;
	}
}