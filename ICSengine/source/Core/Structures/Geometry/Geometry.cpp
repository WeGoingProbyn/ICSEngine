#include "Core/Structures/Geometry/Geometry.h"

Geometry::Geometry()
	:
	m_Indices(MemoryType::ICS_MODEL),
	m_Normals(MemoryType::ICS_MODEL),
	m_Vertices(MemoryType::ICS_MODEL),
	m_TextureCoords(MemoryType::ICS_MODEL)
{
	Vertices::Layout layout(Vertices::Type::Vector3D, Vertices::Type::Normal);
	m_Interleaved = Vertices(layout);
}

Geometry::~Geometry()
{
}

bool Geometry::FindInterleaved()
{
	for (unsigned int root_index = 0; root_index < m_Indices.Size(); root_index++)
	{
		darray<Vector<unsigned int, 3>> tmp;
		for (unsigned int face_index = 0; face_index < m_Indices[root_index].Size(); face_index++)
		{
			Vector<unsigned int, 3> inter_indices;
			for (unsigned int vertex_index = 0; vertex_index < 3u; vertex_index++)
			{
				m_Interleaved.PushVertex(m_Vertices[m_Indices[root_index][face_index][vertex_index]], m_Normals[face_index]);
				if (face_index > 0)
				{
					inter_indices[vertex_index] = (tmp.Size() * 3u) + vertex_index;
				}
				else
				{
					inter_indices[vertex_index] = vertex_index;
				}
			}
			tmp.PushToEnd(inter_indices);
		}
		m_Indexing.PushNode(tmp);
	}
	return true;
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