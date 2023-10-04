#pragma once

#include <Containers/array/darray.h>
#include <Containers/Spatial/Vector.h>
#include "Core/Structures/Buffers/Indices.h"
#include "Core/Structures/Buffers/Vertices.h"
#include "Core/Structures/Spatial/Transformation.h"

class Mesh
{
public:
	ICS_API Mesh();
	
	inline Indices& GetIndices() { return m_Indexing; }
	inline Vertices& GetInterleaved() { return m_Interleaved; }
	inline darray<Transformation>& GetTransforms() { return m_BaseTransforms; }
	inline void PushTransform(Transformation&& transform) { m_BaseTransforms.PushToEnd(std::move(transform)); }

protected:
	Indices m_Indexing;
	Vertices m_Interleaved;
	darray<Transformation> m_BaseTransforms;
};