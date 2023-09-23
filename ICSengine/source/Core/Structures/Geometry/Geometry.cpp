#include "Core/Structures/Geometry/Geometry.h"

Geometry::Geometry()
{
	Vertices::Layout layout(Vertices::Type::Vector3D, Vertices::Type::Normal);
	m_Interleaved = Vertices(layout);
}

Geometry::~Geometry()
{
}


bool Geometry::FindNormals()
{
	for (darray<Vector<unsigned int, 3>>&node : m_Indices)
	{
		for (Vector<unsigned int, 3>&vertex : node)
		{
			// Face normals
			Vector<float, 3> EdgeBA = m_Vertices[vertex[1]] - m_Vertices[vertex[0]];
			Vector<float, 3> EdgeCA = m_Vertices[vertex[2]] - m_Vertices[vertex[0]];
			m_Normals.PushToEnd({ (EdgeBA).CrossProduct(EdgeCA).Normalise() });
		}
	}
	return true;
}

bool Geometry::FindTextureCoords()
{
	return true;
}