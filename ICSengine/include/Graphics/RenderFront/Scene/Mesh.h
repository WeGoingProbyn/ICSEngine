#pragma once

#include "Containers/array/darray.h"
#include "Containers/Spatial/Vector.h"
#include "Graphics/RenderFront/Buffers/Vertices.h"

class Mesh
{
public:
	Mesh();
	inline Vertices& GetInterleaved() { return m_Interleaved; }
	inline darray< darray<Vector<unsigned int, 3>>>& GetIndices() { return m_Indices; }
protected:
	Vertices m_Interleaved;
	darray<Vector<float, 3>> m_Normals;
	darray<Vector<float, 3>> m_Vertices;
	darray<Vector<float, 3>> m_TextureCoords;
	darray<darray<Vector<unsigned int, 3>>> m_Indices;
};