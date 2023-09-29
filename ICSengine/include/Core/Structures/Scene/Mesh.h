#pragma once

#include <Containers/array/darray.h>
#include <Containers/Spatial/Vector.h>
#include "Core/Structures/Buffers/Indices.h"
#include "Core/Structures/Buffers/Vertices.h"

class Mesh
{
public:
	ICS_API Mesh();
	inline Indices& GetIndices() { return m_Indexing; }
	inline Vertices& GetInterleaved() { return m_Interleaved; }
protected:
	Indices m_Indexing;
	Vertices m_Interleaved;
};