#pragma once

#include "Containers/array/varray.h"

varray::varray()
{
	// TODO: Memory checking
	varrayStructure base;
	base.size = 1u;
	base.ptr = nullptr;
	darray<varrayStructure>::m_Ptr[0] = base;
}

varray::~varray()
{
	for (unsigned int index = 0; index < darray<varrayStructure>::m_Size; index++)
	{
		Memory::FreeMemory(darray<varrayStructure>::m_Ptr[index].ptr, darray<varrayStructure>::m_Ptr[index].size, Memory::Type::ICS_ARRAY);
	}
}

varray::varray(void* ptr, unsigned int size)
{
	// TODO: Memory checking
	varrayStructure base;
	base.size = size;
	base.ptr = ptr;
	darray<varrayStructure>::m_Ptr[0] = base;
}