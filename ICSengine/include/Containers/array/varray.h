#pragma once

#include "Containers/array/darray.h"

struct varrayStructure
{
	unsigned int size;
	void* ptr;

};

class varray : public darray<varrayStructure>
{
public:
	varray();
	~varray();
	varray(void* ptr, unsigned int size);
};

#include "varray.inl"